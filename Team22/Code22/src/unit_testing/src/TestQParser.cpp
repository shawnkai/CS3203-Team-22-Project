//
// Created by Atin Sakkeer Hussain on 04/02/2023.
//


#include "QPS/Parser.h"
#include "catch.hpp"


using namespace std;

TEST_CASE("Test Declaration Extraction") {
    QueryParser queryParser;

    string declaration = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;";

    REQUIRE(queryParser.isDeclaration(declaration));

    queryParser.extractDeclarations(declaration);

    vector<tuple<string, string>> result = queryParser.getSynonymTable();

    map<string, string> expectedTable = {{"s", "statement"}, {"s1", "statement"}, {"a", "assign"}, {"a1", "assign"},
                                         {"w", "while"}, {"ifs", "if"}, {"v", "variable"}, {"v1", "variable"},
                                         {"p", "procedure"}, {"q", "procedure"}, {"c", "constant"}, {"re", "read"},
                                         {"pn", "print"}, {"cl", "call"}};

    map<string, string> actualTable;
    for (auto & i : result) {
        actualTable[get<0>(i)] = get<1>(i);
    }

    REQUIRE(actualTable == expectedTable);
}