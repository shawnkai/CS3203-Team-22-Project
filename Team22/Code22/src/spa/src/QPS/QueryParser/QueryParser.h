//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#ifndef SPA_QUERYPARSER_H
#define SPA_QUERYPARSER_H

#include "Utilities.h"
#include "SynonymTable.h"
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
#include "QPS/Expressions/NextExpression/NextExpression.h"
#include "QPS/Expressions/AffectsExpression/AffectsExpression.h"

using namespace std;

class QueryParser {
private:
    regex ISDECLARATIONREGEX = regex(R"lit(((^|;\s?)\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\s+((\w|,\s*)+))+;)lit");
    regex EXTRACTDECLARATIONREGEX = regex(R"((^| |;\s?)\s*(stmt|read|print|call|while|if|assign|variable|constant|procedure)\s+((\w|,\s*)+))");

    /**
     * Sanitizes the given query string by removing extraneous whitespace and replacing certain keywords
     *
     * @param query The query string to sanitize
     * @return The sanitized query string
     */
    static string sanitiseQuery(const string& query);

protected:
    SynonymTable synonymTable;

public:
    /**
     * Constructor for QueryParser class
     */
    QueryParser();

    /**
     * Parses the given query string and returns a SelectExpression object
     *
     * @param query The query string to parse
     * @return A SelectExpression object representing the parsed query
     * @throws SyntacticException If the query string is not valid
     */
    SelectExpression* parse(string query);

    /**
     * Checks if the given query string is a declaration
     *
     * @param query The query string to check
     * @return True if the query string is a declaration, false otherwise
     */
    bool isDeclaration(const string& query);

    /**
     * Checks if the given query string is a valid query
     *
     * @param query The query string to check
     * @return True if the query string is valid, false otherwise
     */
    bool isValidQuery(const string& query);

    /**
     * Extracts declarations from the given query string and adds them to the synonym table
     *
     * @param query The query string to extract declarations from
     */
    void extractDeclarations(string query);

    /**
     * Replaces the "and" keyword in a query string with the appropriate keyword based on the previous clause
     *
     * @param query The query string to process
     * @return The processed query string
     * @throws SyntacticException If the query string is not valid
     */
    static string replaceAnd(string query);

    /**
     * Returns the synonym table used by the parser to map synonyms to their respective design entities.
     *
     * @return the SynonymTable object used by the parser
     */
    SynonymTable getSynonymTable();

};


#endif //SPA_QUERYPARSER_H
