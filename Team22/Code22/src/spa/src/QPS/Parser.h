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
	map<string, DesignEntity> synonymTable;

public:
	QueryParser();

	Expression parse(string query);

	bool isDeclaration(string query);
	bool containsModifiesExpression(string query);
	bool containsUsesExpression(string query);

    void addToSynonymTable(string type, string name);
	void extractDeclarations(string query);

	ModifiesExpression extractModifiesExpression(string query);
	UsesExpression extractUsesExpression(string query);

    vector<tuple<string, string>> getSynonymTable();
};


#endif //SPA_PARSER_H
