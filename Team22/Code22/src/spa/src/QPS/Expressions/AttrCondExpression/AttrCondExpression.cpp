//
// Created by Tanishq Sharma on 10/3/23.
//

#include "AttrCondExpression.h"

#include "Utilities.h"

unordered_map<string, string> AttrCondExpression::attrToType = {{"varName", "STRING"}, {"stmt#", "INT"}, {"procName", "STRING"}, {"value", "INT"}};

AttrCondExpression::AttrCondExpression(DesignEntity *syn1, string syn1attr, DesignEntity *syn2, string syn2attr) : Expression({syn1, syn2}) {
    this->syn1attr = std::move(syn1attr);
    this->syn2attr = std::move(syn2attr);
}

bool AttrCondExpression::containsAttrCondExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), ATTRCONDREGEX), std::sregex_iterator()) > 0;
}

pair<DesignEntity *, pair<string, string>> AttrCondExpression::generateSynAndAttrName(string ref, SynonymTable synonymTable) {
    if (regex_match(ref, regex("[\\w]+\\.(?:\\w|#)+"))) {
        //attribute ref
        string syn_string = ::strtok(ref.data(), ".");
        string attr = ::strtok(NULL, ".");
        DesignEntity *syn = synonymTable.get(syn_string, "select");
        if (!syn->checkAttr(attr)) {
            throw SemanticException();
        }
        return {syn, {attr, AttrCondExpression::attrToType[attr]}};
    } else if (regex_match(ref, regex(R"(\"\w+\")"))) {
        //ident
        DesignEntity *syn = new NamedEntity("ident", ref);
        return {syn, {"", "STRING"}};
    } else if (regex_match(ref, regex("\\d+"))) {
        if (!Utilities::isNumber(ref)) {
            throw SyntacticException();
        }
        //integer
        DesignEntity *syn = new StmtEntity(stoi(ref), true);
        return {syn, {"", "INT"}};
    } else {
        throw SyntacticException();
    }
}

vector<AttrCondExpression *> AttrCondExpression::extractAttrCondExpression(const string &query, const SynonymTable &synonymTable) {
    if (!containsAttrCondExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<AttrCondExpression *> expressions;

    while (regex_search(searchStart, query.cend(), sm, ATTRCONDREGEX)) {
        pair<DesignEntity *, pair<string, string>> arg1 = AttrCondExpression::generateSynAndAttrName(sm.str(1), synonymTable);
        pair<DesignEntity *, pair<string, string>> arg2 = AttrCondExpression::generateSynAndAttrName(sm.str(2), synonymTable);
        if (arg1.second.second != arg2.second.second) {
            throw SemanticException();
        }

        expressions.push_back(new AttrCondExpression(arg1.first, arg1.second.first, arg2.first, arg2.second.first));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

ResultTable *AttrCondExpression::evaluate(PKB pkb) {
    if (dynamic_cast<StmtEntity*>(this->entities[0])) {
        if (syn2attr == "stmt#") {
            if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() <= 0) {
                throw SemanticException();
            }
            vector<Result> lineResults = pkb.getAllDesignEntity("STATEMENT");
            vector<int> lines;
            for (Result res : lineResults) {
                for (const string& line: res.getQueryResult()) {
                    lines.push_back(stoi(line));
                }
            }
            int maxLine = *max_element(lines.begin(), lines.end());
            if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() > maxLine) {
                throw SemanticException();
            }
        }
    } else if (dynamic_cast<StmtEntity*>(this->entities[1])) {
        if (syn1attr == "stmt#") {
            if (dynamic_cast<StmtEntity*>(this->entities[1])->getLine() <= 0) {
                throw SemanticException();
            }
            vector<Result> lineResults = pkb.getAllDesignEntity("STATEMENT");
            vector<int> lines;
            for (Result res : lineResults) {
                for (const string& line: res.getQueryResult()) {
                    lines.push_back(stoi(line));
                }
            }
            int maxLine = *max_element(lines.begin(), lines.end());
            if (dynamic_cast<StmtEntity*>(this->entities[1])->getLine() > maxLine) {
                throw SemanticException();
            }
        }
    }
    // Syn1
    ResultTable *syn1Table = this->entities[0]->getAttrVal(syn1attr, pkb);
    // Syn2
    ResultTable *syn2Table = this->entities[1]->getAttrVal(syn2attr, pkb);
    return syn1Table->intersection(syn2Table)->removeColumn("withCond");
}

string AttrCondExpression::toString() const {
    string res = "with ";
    if (!this->syn1attr.empty()) {
        res += this->entities[0]->toString() + "." + this->syn1attr;
    } else {
        res += this->entities[0]->toString();
    }
    res += " = ";
    if (!this->syn2attr.empty()) {
        res += this->entities[1]->toString() + "." + this->syn2attr;
    } else {
        res += this->entities[1]->toString();
    }
    return res;
}
