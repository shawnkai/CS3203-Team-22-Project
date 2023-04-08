//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "Expressions.h"

#include "PKB/PKB.h"
#include "QPS/Exceptions/Exceptions.h"
#include "Utilities.h"
#include <algorithm>
#include <regex>

string MODIFIES = R"lit(Modifies\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string USES = R"lit(Uses\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PATTERN = R"(pattern\s+(\w+)\s*\(\s*((?:\"?[\w]+\"?)|_)\s*,\s*((?:_?\"[\w\+\-\*\s/%()]+\"_?)|_)(?:\s*,\s*(_))?\s*\))";
string FOLLOWS = R"lit(Follows\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string FOLLOWSSTAR = R"lit(Follows\*\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PARENT = R"lit(Parent\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string PARENTSTAR = R"lit(Parent\*\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))lit";
string ATTRCOND = R"lit(with\s+([\w]+\.(?:\w|#)+|\"\w+\"|\d+)\s*=\s*([\w]+\.(?:\w|#)+|\"\w+\"|\d+))lit";
string CALLS = R"(Calls\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))";
string CALLSSTAR = R"(Calls\*\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))";
string NEXT = R"(Next\s*\(\s*("?\w+"?)\s*,\s*("?\w+"?)\s*\))";
string RETURNVALUE = R"lit(Select\s+(?:([\w]+(?:\.(?:(?:\w|#)+))?)|<\s*((?:([\w]+)(?:\.((?:\w|#)+))?)\s*(\s*,\s*([\w]+)(?:\.((?:\w|#)+))?)+)\s*>))lit";
string Expression::QUERYVALIDATION = RETURNVALUE + R"lit((\s+such\s+that\s+()lit" + MODIFIES + "|" + USES + "|" + FOLLOWS + "|" + FOLLOWSSTAR + "|" + PARENT + "|" + PARENTSTAR + "|" + CALLS + "|" + CALLSSTAR + "|" + NEXT + ")|\\s+" + PATTERN + "|\\s+" + ATTRCOND + ")*";

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
regex Expression::CALLSREGEX = regex(CALLS);
regex Expression::CALLSSTARREGEX = regex(CALLSSTAR);
regex Expression::NEXTREGEX = regex(NEXT);
regex Expression::RETURNVALUEREGEX = regex(RETURNVALUE);

// Function Definitions
Expression::Expression(vector<DesignEntity *> entities) {
    this->entities = std::move(entities);
}

vector<DesignEntity *> Expression::getAllEntities() {
    return this->entities;
}