//
// Created by Tanishq Sharma on 5/3/23.
//

#include "PatternExpression.h"

string PatternExpression::toString() {
    return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", " + this->p2 + ")";
}

PatternExpression::PatternExpression(DesignEntity *entity, NamedEntity* p1, string p2) : Expression({entity}) {
    this->p1 = p1;
    this->p2 = std::move(p2);
}

ResultTable PatternExpression::evaluate(PKB pkb) {
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

bool PatternExpression::containsPatternExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), PATTERNREGEX), std::sregex_iterator()) > 0;
}

vector<PatternExpression*> PatternExpression::extractPatternExpression(const string& query, SynonymTable synonymTable) {
    if (!containsPatternExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<PatternExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, PATTERNREGEX)) {
        string arg3 = sm.str(3);
        arg3 = Utilities::removeAllOccurrences(arg3, ' ');

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

        string arg1 = sm.str(1);

        string arg2 = sm.str(2);

        NamedEntity* a2;
        if (arg2.find('\"') != string::npos) {
            a2 = new NamedEntity("ident", arg2);
        } else if (arg2 == "_") {
            a2 = new WildCardEntity();
        } else {
            a2 = dynamic_cast<NamedEntity*>(synonymTable.get(arg2, "named"));
            if (a2->getType() != "VARIABLE") {
                throw SemanticException();
            }
        }

        auto *a1 = dynamic_cast<StmtEntity*>(synonymTable.get(arg1, "stmt"));

        string infixPattern = Utilities::removeAllOccurrences(arg3, '"');

        if (!Utilities::checkInfixExpression(Utilities::removeAllOccurrences(infixPattern, '_'))) {
            throw SyntacticException();
        }

        string prefixPattern = Utilities::infixToPrefix(infixPattern);
        if (a1->getType() != "ASSIGNMENT") {
            throw SemanticException();
        }
        expressions.push_back(new PatternExpression(a1,  a2, prefixPattern));

        searchStart = sm.suffix().first;
    }

    return expressions;
}