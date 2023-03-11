//
// Created by Tanishq Sharma on 10/3/23.
//

#include "AttrCondExpression.h"

#include "Utilities.h"

AttrCondExpression::AttrCondExpression(DesignEntity *syn1, string syn1attr, DesignEntity *syn2, string syn2attr) : Expression({syn1, syn2}) {
    this->syn1attr = std::move(syn1attr);
    this->syn2attr = std::move(syn2attr);
}

bool AttrCondExpression::containsAttrCondExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), ATTRCONDREGEX), std::sregex_iterator()) > 0;
}

pair<DesignEntity*, string> AttrCondExpression::generateSynAndAttrName(string ref, SynonymTable synonymTable) {
    if (regex_match(ref, regex("[\\w]+.(?:\\w|#)+"))) {
    //attribute ref
        string syn_string = ::strtok(ref.data(), ".");
        string attr = ::strtok(NULL, ".");
        DesignEntity* syn = synonymTable.get(syn_string, "select");
        if (!syn->checkAttr(attr)) {
            throw SemanticException();
        }
        return {syn, attr};
    } else if (regex_match(ref, regex(R"(\"\w+\")"))) {
    //ident
        DesignEntity *syn = new NamedEntity("ident", ref);
        return {syn, NULL};
    } else if (regex_match(ref, regex("\\d+"))) {
    //integer
        DesignEntity *syn = new NamedEntity("int", ref);
        return {syn, NULL};
    } else {
        throw SyntacticException();
    }
}

vector<AttrCondExpression*> AttrCondExpression::extractAttrCondExpression(const string& query, const SynonymTable& synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<AttrCondExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, MODIFIESREGEX)) {
        pair<DesignEntity*, string> arg1 = AttrCondExpression::generateSynAndAttrName(sm.str(1), synonymTable);
        pair<DesignEntity*, string> arg2 = AttrCondExpression::generateSynAndAttrName(sm.str(2), synonymTable);

        expressions.push_back(new AttrCondExpression(arg1.first, arg1.second, arg2.first, arg2.second));

        searchStart = sm.suffix().first;
    }
    return expressions;
}

ResultTable AttrCondExpression::evaluate(PKB pkb) {
    return ResultTable({});
}

string AttrCondExpression::toString() {
    return "(" + this->entities[0]->toString() + "." + this->syn1attr + "=" +
                 this->entities[1]->toString() + "." + this->syn2attr + ")";
}
