#include<stdio.h>

#include "QueryParser.h"

using namespace std;

QueryParser::QueryParser() {}

SelectExpression* QueryParser::parse(string query) {

    vector<Expression*> conditions;
    query = sanitiseQuery(query);
    query = replaceAnd(query);

    if (this->isDeclaration(query) || query.empty()) {
        this->extractDeclarations(query);
        return NULL;
    } else if (this->isValidQuery(query)) {
        pair<vector<DesignEntity*>, vector<string>> synonymsAndAttributes = SelectExpression::extractSynonymsAndAttributes(query, this->synonymTable);

        Utilities::concatenateVectors(conditions, ModifiesExpression::extractModifiesExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, UsesExpression::extractUsesExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, PatternExpression::extractPatternExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, FollowsExpression::extractFollowsExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions,
                                      FollowsStarExpression::extractFollowsStarExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, ParentExpression::extractParentExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions,
                                      ParentStarExpression::extractParentStarExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, AttrCondExpression::extractAttrCondExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, CallsExpression::extractCallsExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, CallsStarExpression::extractCallsStarExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, NextExpression::extractNextExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, NextStarExpression::extractNextStarExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, AffectsExpression::extractAffectsExpression(query, synonymTable));
        Utilities::concatenateVectors(conditions, AffectsStarExpression::extractAffectsStarExpression(query, synonymTable));

        vector<Expression*> uniqueConditions = Utilities::getUniqueElements(conditions);

        return new SelectExpression(synonymsAndAttributes.first, synonymsAndAttributes.second, uniqueConditions);
    } else {
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

    vector<string> subClauses = {"Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies",
                                 "Calls", "Calls*", "Next", "Next*", "Affects", "Affects*"};

    vector<string> split_tokens;

    for ( ; split_iterator != end; ++split_iterator) {
        split_tokens.push_back(split_iterator->str());
    }


    for (int i = 0; i < split_tokens.size(); i++) {
        if (split_tokens[i] == "such-that" || split_tokens[i] == "pattern" || split_tokens[i] == "with") {
            previousClause = split_tokens[i];
            result_query += previousClause + " ";
        } else if (split_tokens[i] == "and") {
            if (previousClause.empty()) {
                throw SyntacticException();
            }
            if (previousClause == "pattern" && std::find(subClauses.begin(), subClauses.end(), split_tokens[i + 1]) != subClauses.end()) {
                previousClause = "such-that";
            }
            result_query += previousClause + " ";
        } else {
            result_query += (split_tokens[i]) + " ";
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
        name = Utilities::removeAllOccurrences(name, ' ');
        unsigned long pos = 0;
        string delimiter = ",";
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

