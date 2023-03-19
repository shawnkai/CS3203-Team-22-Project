//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "Expressions.h"

#include "PKB/PKB.h"
#include <algorithm>
#include <regex>
#include "Utilities.h"
#include "QPS/Exceptions/Exceptions.h"

string MODIFIES = R"lit(Modifies\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string USES = R"lit(Uses\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PATTERN = R"(pattern\s+(\w+)\s*\(\s*((?:\"?[\w]+\"?)|_)\s*,\s*((?:_?\"?[\w\+\-\*\s/%()]+\"?_?)|_)\s*\))";
string FOLLOWS = R"lit(Follows\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string FOLLOWSSTAR = R"lit(Follows\*\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PARENT = R"lit(Parent\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PARENTSTAR = R"lit(Parent\*\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string ATTRCOND = R"lit(with\s+([\w]+\.(?:\w|#)+|\"\w+\"|\d+)\s*=\s*([\w]+\.(?:\w|#)+|\"\w+\"|\d+))lit";
string Expression::QUERYVALIDATION = R"lit(Select\s+([\w]+)(?:\.((?:\w|#)+))?(\s+such\s+that\s+()lit" + MODIFIES + "|" + USES + "|" + FOLLOWS + "|" + FOLLOWSSTAR + "|" + PARENT + "|" + PARENTSTAR  + ")|\\s+" + PATTERN + "|\\s+" + ATTRCOND + ")*";

// Regexes
regex Expression::QUERYVALIDATIONREGEX = regex(QUERYVALIDATION);
regex Expression::MODIFIESREGEX = regex(MODIFIES);
regex Expression::USESREGEX = regex(USES);
regex Expression::PATTERNREGEX = regex(PATTERN);
regex Expression::FOLLOWSREGEX = regex(FOLLOWS);
regex Expression::FOLLOWSSTARREGEX = regex(FOLLOWSSTAR);
regex Expression::PARENTREGEX = regex(PARENT);
regex Expression::PARENTSTARREGEX = regex(PARENTSTAR);
regex Expression::ATTRCONDREGEX = regex(ATTRCOND);

// Function Definitions
Expression::Expression(vector<DesignEntity*> entities) {
    this->entities = std::move(entities);
}

vector<DesignEntity*> Expression::getAllEntities() {
    return this->entities;
}