#include<stdio.h>

#include "Parser.h"
#include "Utilities.h"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

QueryParser::QueryParser() {}

SelectExpression* QueryParser::parse(string query) {vector<Expression*> conditions;

    query = sanitiseQuery(query);
    query = replaceAnd(query);

    if (this->isDeclaration(query) || query.empty()) {
        this->extractDeclarations(query);
        return NULL;
    } else if (this->isValidQuery(query)) {
        smatch sm;
        regex_search(query, sm, RETURNVALUEREGEX);

        DesignEntity *arg = this->synonymTable.get(sm.str(1), "select");
        string attr = sm.str(2);

        if (ModifiesExpression::containsModifiesExpression(query)) {
            vector<ModifiesExpression*> modifiesConditions = ModifiesExpression::extractModifiesExpression(query, synonymTable);
            for (ModifiesExpression *e : modifiesConditions) {
                conditions.push_back(e);
            }
        }

        if (UsesExpression::containsUsesExpression(query)) {
            vector<UsesExpression*> usesConditions = UsesExpression::extractUsesExpression(query, synonymTable);
            for (UsesExpression *e : usesConditions) {
                conditions.push_back(e);
            }
        }

        if (PatternExpression::containsPatternExpression(query)) {
            vector<PatternExpression*> patternConditions = PatternExpression::extractPatternExpression(query, synonymTable);
            for (PatternExpression *e : patternConditions) {
                conditions.push_back(e);
            }
        }

        if (FollowsExpression::containsFollowsExpression(query)) {vector<FollowsExpression*> followsConditions = FollowsExpression::extractFollowsExpression(query, synonymTable);
            for (FollowsExpression *e : followsConditions) {
                conditions.push_back(e);
            }
        }

        if (FollowsStarExpression::containsFollowsStarExpression(query)) {
            vector<FollowsStarExpression*> followsStarConditions = FollowsStarExpression::extractFollowsStarExpression(query, synonymTable);
            for (FollowsStarExpression *e : followsStarConditions) {
                conditions.push_back(e);
            }
        }

        if (ParentExpression::containsParentExpression(query)) {
            vector<ParentExpression*> parentConditions = ParentExpression::extractParentExpression(query, synonymTable);for (ParentExpression *e : parentConditions) {
                conditions.push_back(e);
            }
        }

        if (ParentStarExpression::containsParentStarExpression(query)) {
            vector<ParentStarExpression*> parentStarConditions = ParentStarExpression::extractParentStarExpression(query, synonymTable);
            for (ParentStarExpression *e : parentStarConditions) {
                conditions.push_back(e);
            }
        }

        if (AttrCondExpression::containsAttrCondExpression(query)) {
            vector<AttrCondExpression*> AttrCondClauses = AttrCondExpression::extractAttrCondExpression(query, synonymTable);
            for (AttrCondExpression *e : AttrCondClauses) {
                conditions.push_back(e);
            }
        }
        if (attr.empty()) {
            return new SelectExpression(arg, conditions);
        }
        return new SelectExpression(arg, conditions, attr);
    } else {
        ::printf("%s\n", Expression::QUERYVALIDATION.c_str());
        throw SyntacticException();
    }
}

string QueryParser::sanitiseQuery(const string& query) {
    string result_query = regex_replace(query, std::regex("^ +| +$|( ) +"), "$1");
    result_query = regex_replace(result_query, std::regex(R"(\s+(?=(?:(?:[^"]*"){2})*[^"]*"[^"]*$))"), "$1");
    return result_query;
}



string QueryParser::replaceAnd(string query) {
    string previousClause;

    query = regex_replace(query, std::regex("such that"), "such-that");

    regex split("\\s+");
    sregex_token_iterator split_iterator(query.begin(), query.end(), split, -1);
    sregex_token_iterator end;

    string result_query;

    for ( ; split_iterator != end; ++split_iterator) {
        if (split_iterator->str() == "such-that" || split_iterator->str() == "pattern" || split_iterator->str() == "with") {
            previousClause = split_iterator->str();
            result_query += previousClause + " ";
        } else if (split_iterator->str() == "and") {
            if (previousClause.empty()) {
                throw SyntacticException();
            }
            result_query += previousClause + " ";
        } else {
            result_query += (split_iterator->str()) + " ";
        }
    }

    result_query = regex_replace(result_query, regex("such-that"), "such that");
    result_query.pop_back();
    return result_query;
}

bool QueryParser::isValidQuery(const string& query) {
    return regex_match(query, Expression::QUERYVALIDATIONREGEX);
}

bool QueryParser::isDeclaration(const string& query) {
    return regex_match(query, ISDECLARATIONREGEX);
}

void QueryParser::extractDeclarations(string query) {
    smatch sm;
    auto begin = sregex_iterator(query.begin(), query.end(), EXTRACTDECLARATIONREGEX);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        string type = match.str(2);
        string name =  match.str(3);

        unsigned long pos = 0;
        string delimiter = ", ";
        if (name.find(delimiter) != std::string::npos) {
            while ((pos = name.find(delimiter)) != std::string::npos) {
                string subname = name.substr(0, pos);
                if (subname.empty()) {
                    break;
                }
                this->synonymTable.add(type, subname);
                name.erase(0, pos + delimiter.length());
            }
        }
        if (!name.empty()) {
            this->synonymTable.add(type, name);
        }
    }
}

SynonymTable QueryParser::getSynonymTable() {
    return this->synonymTable;
}

