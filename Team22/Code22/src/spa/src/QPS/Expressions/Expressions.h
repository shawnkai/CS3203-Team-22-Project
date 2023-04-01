//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#ifndef SPA_EXPRESSIONS_H
#define SPA_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>
#include <regex>

#include "QPS/Entities/Entities.h"
#include "PKB/PKB.h"
#include "QPS/Evaluator/ResultTable.h"
#include "QPS/Exceptions/Exceptions.h"
#include "QPS/Parser/SynonymTable.h"
#include "Result.h"
#include "Utilities.h"

using namespace std;

class Expression {
    /**
     * This is the parent class for all expressions and contains the virtual functions evaluate() and toString()
     * which overridden by its child classes
     */
    protected:
        vector<DesignEntity*> entities;

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
        static regex RETURNVALUEREGEX;

public:
        static string QUERYVALIDATION;
        static regex QUERYVALIDATIONREGEX;

    explicit Expression(vector<DesignEntity*> entities);

        virtual ResultTable* evaluate(PKB pkb) = 0;

        vector<DesignEntity*> getAllEntities();

        virtual string toString() = 0;
};

#endif //SPA_EXPRESSIONS_H
