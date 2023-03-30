//
// Created by Tanishq Sharma on 5/3/23.
//

#include "PatternExpression.h"

#include <utility>

PatternExpression::PatternExpression(DesignEntity *entity, NamedEntity* p1) : Expression({entity}) {
    this->p1 = p1;
}

AssignPatternExpression::AssignPatternExpression(DesignEntity *entity, NamedEntity *p1, string p2) : PatternExpression(entity, p1) {
    this->p2 = std::move(p2);
}

bool PatternExpression::containsPatternExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), PATTERNREGEX), std::sregex_iterator()) > 0;
}

IfWhilePatternExpression::IfWhilePatternExpression(DesignEntity *entity, NamedEntity *p1) : PatternExpression(entity, p1) {}

vector<PatternExpression*> PatternExpression::extractPatternExpression(const string& query, SynonymTable synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<PatternExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, PATTERNREGEX)) {

        string arg4 = sm.str(4);
        arg4 = Utilities::removeAllOccurrences(arg4, ' ');

        string arg3 = sm.str(3);
        arg3 = Utilities::removeAllOccurrences(arg3, ' ');

        string arg1 = sm.str(1);
        auto *a1 = dynamic_cast<StmtRef*>(synonymTable.get(arg1, "select"));

        //check for if
        if (!arg4.empty() && (arg4 != "_" || arg3 != "_")) {
            throw SyntacticException();
        }

        //check for while
        if (a1->getType() == "WHILE" && arg3 != "_") {
            throw SyntacticException();
        }

        if (a1->getType() == "IF" && arg4.empty()) {
            throw SyntacticException();
        }

        if (a1->getType() != "IF" && !arg4.empty()) {
            throw SyntacticException();
        }

        //check for assign
        if (arg3.size() == 1 && arg3[0] != '_') {
            throw SyntacticException();
        } else if (arg3.size() != 1) {
            if (arg3.find('\"') == string::npos) {
                throw SyntacticException();
            } else if (arg3[0] == '_' && arg3[arg3.size() - 1] != '_') {
                throw SyntacticException();
            } else if (arg3[0] != '_' && (arg3[0] != '\"' || arg3[arg3.size() - 1] != '\"')) {
                throw SyntacticException();
            } else if (arg3[0] == '_' && (arg3[1] != '\"' || arg3[arg3.size() - 2] != '\"')) {
                throw SyntacticException();
            } else if (!regex_match(arg3, regex(R"(_?\"[A-Za-z0-9+\-*/%)(]+\"_?)"))) {
                throw SyntacticException();
            }
        }

        string arg2 = sm.str(2);
        NamedEntity* a2;

        if (arg2.find('\"') != string::npos) {
            a2 = new NamedEntity("ident", arg2);
        } else if (arg2 == "_") {
            a2 = new WildcardNamedEntity();
        } else {
            a2 = dynamic_cast<NamedEntity*>(synonymTable.get(arg2, "named"));
            if (a2->getType() != "VARIABLE") {
                throw SemanticException();
            }
        }

        string a1type = a1->getType();

        if (a1type == "WHILE" || a1type == "IF") {
            expressions.push_back(new IfWhilePatternExpression(a1, a2));
        } else if (a1type == "ASSIGNMENT") {
            string infixPattern = Utilities::removeAllOccurrences(arg3, '"');
            if (!Utilities::checkInfixExpression(Utilities::removeAllOccurrences(infixPattern, '_'))) {
                throw SyntacticException();
            }
            string prefixPattern = Utilities::infixToPrefix(infixPattern);
            expressions.push_back(new AssignPatternExpression(a1,  a2, prefixPattern));
        } else {
            throw SemanticException();
        }


        searchStart = sm.suffix().first;
    }

    return expressions;
}

ResultTable AssignPatternExpression::evaluate(PKB pkb) {
    string prefix_expr = p2;
    prefix_expr = Utilities::removeAllOccurrences(prefix_expr, '\"');
    prefix_expr = regex_replace(prefix_expr, regex("\\-"), "\\-");
    prefix_expr = regex_replace(prefix_expr, regex("\\+"), "\\+");
    prefix_expr = regex_replace(prefix_expr, regex("\\*"), "\\*");
    prefix_expr = regex_replace(prefix_expr, regex("_"), R"([\w\+\-\*/%]*)");
    regex right_expr (prefix_expr);

    if (p1->getSynonym() == "_" || p1->getType() == "VARIABLE") {
        auto key_values = pkb.getAllRightHandExpressions();
        vector<string> results;
        map<string, vector<string>> altResults = {{this->entities[0]->toString(), {}}, {p1->getSynonym(), {}}};
        for (const auto& pattern : key_values) {
            for (const auto& line_exp: pattern.second) {
                if (regex_match(line_exp.second, right_expr)) {
                    altResults.find(this->entities[0]->toString())->second.push_back(line_exp.first);
                    altResults.find(p1->getSynonym())->second.push_back(pattern.first);
                }
            }
        }
        if (p1->getSynonym() == "_") {
            return ResultTable({make_pair(this->entities[0]->toString(), altResults.find(this->entities[0]->toString())->second)});
        }
        return ResultTable(altResults);
    } else {
        auto key_values = pkb.getAllRightHandExpressionsOfAVariable(p1->getSynonym());
        vector<string> result;
        for (const auto& pair : key_values) {
            if (regex_match(pair.second, right_expr)) {
                result.push_back(pair.first);
            }
        }
        return ResultTable({make_pair(this->entities[0]->toString(), result)});
    }
}

ResultTable IfWhilePatternExpression::evaluate(PKB pkb) {
    vector<Result> all_entities = pkb.getAllDesignEntity(this->entities[0]->getType());
    string col1 = this->entities[0]->toString();
    string col2 = this->p1->toString();

    if (this->p1->getType() == "ident") {
        map<string, vector<string>> results = {{col1, {}}};
        string var = Utilities::removeAllOccurrences(col2, '\"');
        for (Result entity : all_entities) {
            for (const string& line : entity.getQueryResult()) {
                if (pkb.isVariableUsedInPattern(this->entities[0]->getType(), line, var)) {
                    results[col1].push_back(line);
                }
            }
        }
        return ResultTable(results);
    } else {
        map<string, vector<string>> results = {{col1, {}}, {col2, {}}};
        vector<string> matches;
        for (Result entity : all_entities) {
            for (const string& line : entity.getQueryResult()) {
                unordered_set<string> sub_res = pkb.getAllVariablesUsedInPattern(this->entities[0]->getType(), line);
                for(const string& var : sub_res) {
                    results[col1].push_back(line);
                    results[col2].push_back(var);
                }
            }
        }
        if (this->p1->getType() == "WILDCARD") {
            return ResultTable(results).getColumns({col1});
        }
        return ResultTable(results);
    }
}

string AssignPatternExpression::toString() {
    return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", " + this->p2 + ")";
}

string IfWhilePatternExpression::toString() {
    if (this->entities[0]->getType() == "IF") {
        return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", _, _)";
    }
    return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", _)";
}

