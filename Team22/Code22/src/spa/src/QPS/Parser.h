//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#ifndef SPA_PARSER_H
#define SPA_PARSER_H

#include "QPS/Expressions.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <tuple>

using namespace std;

bool isNumber(string s);

class QueryParser {

protected:
	map<string, DesignEntity*> synonymTable;

public:
	QueryParser();

	SelectExpression *parse(const string& query);

	bool isDeclaration(const string& query);
	bool containsModifiesExpression(string query);
	bool containsUsesExpression(string query);
    bool containsPatternExpression(string query);

    void addToSynonymTable(string type, const string& name);
	void extractDeclarations(string query);

	vector<ModifiesExpression*> extractModifiesExpression(const string& query);
	vector<UsesExpression*> extractUsesExpression(const string& query);
    vector<PatternExpression*> extractPatternExpression(const string& query);

    vector<tuple<string, string>> getSynonymTable();
};


#endif //SPA_PARSER_H
