//
// Created by Tanishq Sharma on 02/03/2023.
//
#include "catch.hpp"
#include "QPS/Evaluator/ResultTable.h"

TEST_CASE("TestCase1_MatchingSingleColumnMatchingRows") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"1", "2", "2", "3", "4", "5"}),
                                           make_pair<string, vector<string>>("s1", {"6", "7", "11", "8", "9", "10"})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"2", "4", "4"}),
                                           make_pair<string, vector<string>>("v", {"x", "x", "y"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s", {"2", "2", "4", "4"}),
                                                  make_pair<string, vector<string>>("s1", {"7", "11", "9", "9"}),
                                                  make_pair<string, vector<string>>("v", {"x", "x", "x", "y"})});

    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase2_MatchingSingleColumnNoMatchingRows") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"1", "2", "2", "3", "4", "5"}),
                                           make_pair<string, vector<string>>("s1", {"6", "7", "11", "8", "9", "10"})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"6", "7", "8"}),
                                           make_pair<string, vector<string>>("v", {"x", "x", "y"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s", {}),
                                                  make_pair<string, vector<string>>("s1", {}),
                                                  make_pair<string, vector<string>>("v", {})});

    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}


TEST_CASE("TestCase3_MatchingRowsInMatchingColumns") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"1", "2", "2", "3", "4", "5"}),
                                           make_pair<string, vector<string>>("s1", {"6", "7", "11", "8", "9", "10"})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"2", "4", "4", "4"}),
                                           make_pair<string, vector<string>>("s1", {"7", "4", "9", "9"}),
                                           make_pair<string, vector<string>>("v", {"x", "x", "y", "z"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s", {"2", "4", "4"}),
                                                  make_pair<string, vector<string>>("s1", {"7", "9", "9"}),
                                                  make_pair<string, vector<string>>("v", {"x", "y", "z"})});


    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase4_MatchingRowsInMatchingColumnsDifferentColumnOrder") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"1", "2", "2", "3", "4", "5"}),
                                           make_pair<string, vector<string>>("s1", {"6", "7", "11", "8", "9", "10"})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s", {"2", "4", "4", "4"}),
                                           make_pair<string, vector<string>>("v", {"x", "x", "y", "z"}),
                                           make_pair<string, vector<string>>("s1", {"7", "4", "9", "9"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s", {"2", "4", "4"}),
                                                  make_pair<string, vector<string>>("v", {"x", "y", "z"}),
                                                  make_pair<string, vector<string>>("s1", {"7", "9", "9"})});


    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}


TEST_CASE("TestCase5_NoMatchingColumnsAllUniqueCells") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {"1", "2"}),
                                           make_pair<string, vector<string>>("s2", {"6", "7"})});

    auto* table2 = new ResultTable({make_pair<string, vector<string>>("s3", {"3", "4"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s1", {"1", "1", "2", "2"}),
                                                  make_pair<string, vector<string>>("s2", {"6", "6", "7", "7"}),
                                                  make_pair<string, vector<string>>("s3", {"3", "4", "3", "4"}),
                                          });
    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}


TEST_CASE("TestCase6_NoMatchingColumnsRecurringCells") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {"1", "2"}),
                                           make_pair<string, vector<string>>("s2", {"6", "7"})});

    auto* table2 = new ResultTable({make_pair<string, vector<string>>("s3", {"2", "6"})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s1", {"1", "1", "2", "2"}),
                                                  make_pair<string, vector<string>>("s2", {"6", "6", "7", "7"}),
                                                  make_pair<string, vector<string>>("s3", {"2", "6", "2", "6"}),
                                          });
    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase7_MatchingColumnsOneTableEmpty") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {"1", "2"}),
                                           make_pair<string, vector<string>>("s2", {"6", "7"})});

    auto* table2 = new ResultTable({make_pair<string, vector<string>>("s2", {})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s1", {}),
                                                  make_pair<string, vector<string>>("s2", {}),
                                          });
    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase8_NoMatchingColumnsOneTableEmpty") {
    auto* table1 = new ResultTable({make_pair<string, vector<string>>("s3", {})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {"1", "2"}),
                                           make_pair<string, vector<string>>("s2", {"6", "7"})});

    REQUIRE((new BooleanFalseTable())->equals(table1->intersection(table2)));
    REQUIRE((new BooleanFalseTable())->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase9_NoMatchingColumnsBothTablesEmpty_ReturnFirstTable") {
    auto* table1 = new ResultTable({make_pair<string, vector<string>>("s3", {})});

    auto* table2 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {}),
                                           make_pair<string, vector<string>>("s2", {})});

    REQUIRE((new BooleanFalseTable())->equals(table1->intersection(table2)));
    REQUIRE((new BooleanFalseTable())->equals(table2->intersection(table1)));
}

TEST_CASE("TestCase10_MatchingColumnsBothTablesEmpty") {
    auto* table1 = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {}),
                                           make_pair<string, vector<string>>("s2", {})});

    auto* table2 = new ResultTable({make_pair<string, vector<string>>("s2", {})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s1", {}),
                                                  make_pair<string, vector<string>>("s2", {}),
                                          });
    REQUIRE(expectedTable->equals(table1->intersection(table2)));
    REQUIRE(expectedTable->equals(table2->intersection(table1)));
}


//test cases for getColumn
TEST_CASE("TestCase10_GetSingleColumnExists_Success") {
    auto* table = new ResultTable({
                                           make_pair<string, vector<string>>("s1", {}),
                                           make_pair<string, vector<string>>("s2", {})});

    auto* expectedTable = new ResultTable({
                                                  make_pair<string, vector<string>>("s1", {}),
                                          });

    REQUIRE(table->getColumns({"s1"})->equals(expectedTable));
}

TEST_CASE("TestCase10_GetSingleColumnWhichDoesNotExist_EmptyTable") {
    auto* table = new ResultTable({
                                          make_pair<string, vector<string>>("a", {}),
                                          make_pair<string, vector<string>>("b", {})});

    auto* expectedTable = new ResultTable({});

    REQUIRE(table->getColumns({"s1"})->equals(expectedTable));
}

