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

class QueryParser {
private:
    string RETURNVALUE = R"lit(Select\s*(\w+))lit";
    string ISDECLARATION = R"lit(((^|;\s?)\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\s+((\w|,?)+))+;)lit";
    string CONTAINSMODIFIES = R"lit(Modifies\s*\("?(\w+)"?,"?(\w+)"?\))lit";
    string CONTAINSUSES = R"lit(Uses\s*\("?(\w+)"?,"?(\w+)"?\))lit";
    string CONTAINSFOLLOWS = R"lit(Follows\s*\((\w+),(\w+)\))lit";
    string CONTAINSFOLLOWSSTAR = R"lit(Follows\*\s*\((\w+),(\w+)\))lit";
    string CONTAINSPARENT = R"lit(Parent\s*\((\w+),(\w+)\))lit";
    string CONTAINSPARENTSTAR = R"lit(Parent\*\s*\((\w+),(\w+)\))lit";
    string CONTAINSPATTERN = R"(pattern\s+(\w+)\s*\(((?:_?\"?[\w]+\"?_?)|_),((?:_?\"?[\w\+\-\*\s/%)(]+\"?_?)|_)\))";
    string MODIFIES = R"lit(Modifies\s*\(("?\w+"?),("?\w+"?)\))lit";
    string USES = R"lit(Uses\s*\(("?\w+"?),("?\w+"?)\))lit";
    string PATTERN = R"(pattern\s+(\w+)\s*\(((?:\"?[\w]+\"?)|_),((?:_?\"?[\w\+\-\*\s()/%]+\"?_?)|_)\))";
    string FOLLOWS = R"lit(Follows\s*\(("?\w+"?),("?\w+"?)\))lit";
    string FOLLOWSSTAR = R"lit(Follows\*\s*\(("?\w+"?),("?\w+"?)\))lit";
    string PARENT = R"lit(Parent\s*\(("?\w+"?),("?\w+"?)\))lit";
    string PARENTSTAR = R"lit(Parent\*\s*\(("?\w+"?),\s*("?\w+"?)\s*\))lit";
    string EXTRACTDECLARATION = "(^| |;\\s?)\\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\\s+((\\w|,\\s*?)+)";
    string QUERYVALIDATION = R"lit(Select\s+\w+(\s+such\s+that\s+()lit" + CONTAINSMODIFIES + "|" + CONTAINSUSES + "|" + CONTAINSFOLLOWS + "|" + CONTAINSFOLLOWSSTAR + "|" + CONTAINSPARENT + "|" + CONTAINSPARENTSTAR  + ")|\\s+"+ CONTAINSPATTERN +")*";

    // Regexes
    regex RETURNVALUEREGEX = regex(RETURNVALUE);
    regex QUERYVALIDATIONREGEX = regex(QUERYVALIDATION);
    regex ISDECLARATIONREGEX = regex(ISDECLARATION);
    regex CONTAINSMODIFIESREGEX = regex(CONTAINSMODIFIES);
    regex CONTAINSUSESREGEX = regex(CONTAINSUSES);
    regex CONTAINSFOLLOWSREGEX = regex(CONTAINSFOLLOWS);
    regex CONTAINSFOLLOWSSTARREGEX = regex(CONTAINSFOLLOWSSTAR);
    regex CONTAINSPARENTREGEX = regex(CONTAINSPARENT);
    regex CONTAINSPARENTSTARREGEX = regex(CONTAINSPARENTSTAR);
    regex CONTAINSPATTERNREGEX = regex(CONTAINSPATTERN);
    regex MODIFIESREGEX = regex(MODIFIES);
    regex USESREGEX = regex(USES);
    regex PATTERNREGEX = regex(PATTERN);
    regex FOLLOWSREGEX = regex(FOLLOWS);
    regex FOLLOWSSTARREGEX = regex(FOLLOWSSTAR);
    regex PARENTREGEX = regex(PARENT);
    regex PARENTSTARREGEX = regex(PARENTSTAR);
    regex EXTRACTDECLARATIONREGEX = regex(EXTRACTDECLARATION);

    static string sanitiseQuery(string query);


protected:
	map<string, DesignEntity*> synonymTable;

public:
	QueryParser();

    SelectExpression* parse(string query);

	bool isDeclaration(const string& query);
	bool containsModifiesExpression(string query);
	bool containsUsesExpression(string query);
    bool containsPatternExpression(string query);

    tuple<StmtEntity*, StmtEntity*> generateStmtEntityPair(string arg1, string arg2);
    bool isValidQuery(const string& query);
    bool containsFollowsExpression(string query);
    bool containsFollowsStarExpression(string query);
    bool containsParentExpression(string query);
    bool containsParentStarExpression(string query);

    void addToSynonymTable(string type, const string& name);
	void extractDeclarations(string query);

	vector<ModifiesExpression*> extractModifiesExpression(const string& query);
	vector<UsesExpression*> extractUsesExpression(const string& query);
    vector<PatternExpression*> extractPatternExpression(const string& query);
    vector<FollowsExpression*> extractFollowsExpression(const string& query);
    vector<FollowsStarExpression*> extractFollowsStarExpression(const string& query);
    vector<ParentExpression*> extractParentExpression(const string& query);
    vector<ParentStarExpression*> extractParentStarExpression(const string& query);

    vector<tuple<string, string>> getSynonymTable();
    DesignEntity *getFromSynonymTable(const string& name, const string& desiredType);
};


#endif //SPA_PARSER_H
