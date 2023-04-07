//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#ifndef SPA_PARSER_H
#define SPA_PARSER_H

#include "Utilities.h"
#include "QPS/Exceptions/Exceptions.h"
#include "QPS/Expressions/Expressions.h"
#include "QPS/Expressions/SelectExpression/SelectExpression.h"
#include "QPS/Expressions/ModifiesExpression/ModifiesExpression.h"
#include "QPS/Expressions/UsesExpression/UsesExpression.h"
#include "QPS/Expressions/PatternExpression/PatternExpression.h"
#include "QPS/Expressions/FAPSExpression/FAPSExpression.h"
#include "QPS/Expressions/FAPSExpression/FAPSExpression.h"
#include "QPS/Expressions/AttrCondExpression/AttrCondExpression.h"
#include "QPS/Expressions/CallsExpression/CallsExpression.h"
#include "QPS/Expressions/NextExpression//NextExpression.h"

using namespace std;

class QueryParser {
private:
    static string sanitiseQuery(const string& query);

    regex ISDECLARATIONREGEX = regex(R"lit(((^|;\s?)\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\s+((\w|,\s*)+))+;)lit");
    regex EXTRACTDECLARATIONREGEX = regex(R"((^| |;\s?)\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\s+((\w|,\s*)+))");

protected:
    SynonymTable synonymTable;

public:
    QueryParser();

    SelectExpression* parse(string query);

    bool isDeclaration(const string& query);

    bool isValidQuery(const string& query);

    void extractDeclarations(string query);

    static string replaceAnd(string query);

    SynonymTable getSynonymTable();

};


#endif //SPA_PARSER_H
