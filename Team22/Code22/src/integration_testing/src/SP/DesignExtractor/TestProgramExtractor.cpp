#include "SP/DesignExtractor/ProgramExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractSimpleProgram_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 1, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 1, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(variable1);
    read1.children = child3;

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(read1);
    stmtlist1.children = child2;

    TNode procedure1 = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(stmtlist1);
    procedure1.children = child1;

    TNode root = TNode(TokenType::PROGRAM, "program", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(procedure1);
    root.children = child;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ProgramExtractor programExtractor;

    programExtractor.extractAbstraction(root, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString();
    REQUIRE(result1 == "VARIABLE: x: 1, ");
    REQUIRE(result2 == "MODIFIES:STATEMENT: x: 1, ");*/
}

TEST_CASE("Testcase2_ExtractProgramWithMultipleProcedures_ShouldSuccess") {
    TNode variable1 = TNode(TokenType::NAME_IDENTIFIER, "x", 3, std::vector<TNode>(0));
    TNode read1 = TNode(TokenType::READ, "read", 3, std::vector<TNode>(0));
    std::vector<TNode> child7;
    child7.push_back(variable1);
    read1.children = child7;

    TNode stmtlist3 = TNode(TokenType::STATEMENT_LIST, "stmtList", 3, std::vector<TNode>(0));
    std::vector<TNode> child6;
    child6.push_back(read1);
    stmtlist3.children = child6;

    TNode procedure3 = TNode(TokenType::PROCEDURE, "p3", 3, std::vector<TNode>(0));
    std::vector<TNode> child5;
    child5.push_back(stmtlist3);
    procedure3.children = child5;

    TNode call2 = TNode(TokenType::CALL, "p3", 2, std::vector<TNode>(0));

    TNode stmtlist2 = TNode(TokenType::STATEMENT_LIST, "stmtList", 2, std::vector<TNode>(0));
    std::vector<TNode> child4;
    child4.push_back(call2);
    stmtlist2.children = child4;

    TNode procedure2 = TNode(TokenType::PROCEDURE, "p2", 2, std::vector<TNode>(0));
    std::vector<TNode> child3;
    child3.push_back(stmtlist2);
    procedure2.children = child3;

    TNode call1 = TNode(TokenType::CALL, "p2", 1, std::vector<TNode>(0));

    TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
    std::vector<TNode> child2;
    child2.push_back(call1);
    stmtlist1.children = child2;

    TNode procedure1 = TNode(TokenType::PROCEDURE, "p1", 0, std::vector<TNode>(0));
    std::vector<TNode> child1;
    child1.push_back(stmtlist1);
    procedure1.children = child1;

    TNode root = TNode(TokenType::PROGRAM, "program", 0, std::vector<TNode>(0));
    std::vector<TNode> child;
    child.push_back(procedure1);
    child.push_back(procedure2);
    child.push_back(procedure3);
    root.children = child;

    /*PKB pkbinstance = PKB();
    pkbinstance.clearAllDatabases();
    ProgramExtractor programExtractor;

    programExtractor.extractAbstraction(root, pkbinstance);

    std::string result1 = pkbinstance.getDesignEntity("VARIABLE", "x").toString();
    std::string result2 = pkbinstance.getDesignEntity("CALL", "p3").toString();
    std::string result3 = pkbinstance.getDesignAbstraction("CALLS", make_tuple("_", "p2")).toString();
    std::string result4 = pkbinstance.getDesignAbstraction("CALLSSTAR", make_tuple("_", "p1")).toString();
    std::string result5 = pkbinstance.getDesignAbstraction("INVERSECALLS", make_tuple("_", "p3")).toString();
    std::string result6 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "p1")).toString();
    std::string result7 = pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "1")).toString();

    REQUIRE(result1 == "VARIABLE: x: 3, ");
    REQUIRE(result2 == "CALL: p3: 2, ");
    REQUIRE(result3 == "CALLS: p2: p3, ");
    REQUIRE(result4 == "CALLSSTAR: p1: p2, p3, ");
    REQUIRE(result5 == "INVERSECALLS: p3: p1, p2, ");
    REQUIRE(result6 == "MODIFIES:PROCEDURE: p1: 3, ");
    REQUIRE(result7 == "MODIFIES:PROCEDURECALL: 1: 3, ");*/
}