//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#ifndef SPA_EXPRESSIONS_H
#define SPA_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>
#include <regex>

#include "QPS/Entities/StmtRef/StmtRef.h"
#include "QPS/Entities/NamedEntity/NamedEntity.h"
#include "PKB/PKB.h"
#include "QPS/Evaluator/ResultTable.h"
#include "QPS/Exceptions/Exceptions.h"
#include "QPS/QueryParser/SynonymTable.h"
#include "Result.h"
#include "Utilities.h"

using namespace std;

/**
 * Expression is the parent class for all expressions in the query evaluator.
 * It contains the virtual functions evaluate() and toString() which are overridden by its child classes.
 */
class Expression {
    protected:
        vector<DesignEntity*> entities; /**< A vector containing all DesignEntities related to the expression */

        // Regexes
        static regex MODIFIESREGEX;
        static regex USESREGEX;
        static regex PATTERNREGEX;
        static regex FOLLOWSREGEX;
        static regex FOLLOWSSTARREGEX;
        static regex PARENTREGEX;
        static regex PARENTSTARREGEX;
        static regex ATTRCONDREGEX;
        static regex CALLSREGEX;
        static regex CALLSSTARREGEX;
        static regex NEXTREGEX;
        static regex NEXTSTARREGEX;
        static regex AFFECTSREGEX;
        static regex AFFECTSSTARREGEX;
        static regex RETURNVALUEREGEX;

        /**
        * Generate a pair of StmtRef pointers based on two input strings and the SynonymTable containing their entities.
         *
        * @param arg1 The first argument string
        * @param arg2 The second argument string
        * @param synonymTable The SynonymTable containing the entities
         *
        * @return A pair of StmtRef pointers generated from the input strings and SynonymTable
        */
        static pair<StmtRef*, StmtRef*> generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable);

public:
        static string QUERYVALIDATION;
        static regex QUERYVALIDATIONREGEX;

        /**
        * Expression constructor.
         *
        * @param entities A vector containing all DesignEntities related to the expression
        */
        explicit Expression(vector<DesignEntity*> entities);

        /**
        * Virtual function to be implemented by child classes to evaluate the expression.
         *
        * @param pkb The Program Knowledge Base
         *
        * @return A ResultTable containing the results of the evaluation
        */
        virtual ResultTable* evaluate(PKB pkb) = 0;

        /**
        * Get all DesignEntities related to the expression.
        *
        * @return A vector containing all DesignEntities related to the expression
        */
        vector<DesignEntity*> getAllEntities();

        /**
        * Convert the expression to a string.
         *
        * @return A string representation of the expression
        */
        virtual string toString() const = 0;

        /***
         * Get the Synonym Entities used in the Expression
         *
         * @return a vector of synonym entity strings
         */
        vector<string> getSynEntities();
};

#endif //SPA_EXPRESSIONS_H
