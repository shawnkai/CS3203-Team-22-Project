//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#include "QPS/Parser/Parser.h"
#include "QPS/Optimizer/Optimizer.h"
#include "catch.hpp"

TEST_CASE("TestCase1_TestGrouping") {
    QueryParser queryParser;
    string declaration = "stmt s1, s2, s3, s4, s5; variable v;";
    string query = "Select <s1, s5> such that Modifies(s3, \"x\") and Parent(s3, s1) and Uses(s1, v) "
                   "and Next*(s3, s2) and Parent*(s3, s2) and Next*(s4, 18) and Parent*(s5, s4) and Next*(s5, 22)";

    queryParser.parse(declaration);

    SelectExpression *actualResult = queryParser.parse(query);

    auto result = QueryOptimizer::createGroups(actualResult->getConditions());

    for (int i = 0; i < result.size(); i++) {
        ::printf("Group %d: ", i + 1);
        for (Expression * exp : result[i]) {
            ::printf("%s, ", exp->toString().c_str());
        }
        ::printf("\n");
    }
}