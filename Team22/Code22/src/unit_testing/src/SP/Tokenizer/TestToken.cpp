//
// Created by Yi Zhang on 18/2/23.
//
#include "SP/Tokenizer/Token.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("TestCase1_TokenConstructor_ShouldSuccess") {
    Token t1 = Token(TokenType::STATEMENT_LIST, "stmtList", 1);
    Token t2 = Token(TokenType::PRINT, "print", 6);

    REQUIRE(t1.type == TokenType::STATEMENT_LIST);
    REQUIRE(t1.value == "stmtList");
    REQUIRE(t2.type == TokenType::PRINT);
    REQUIRE(t2.lineNumber == 6);
}

TEST_CASE("TestCase2_TokenToString_ShouldSuccess") {
    Token t1 = Token(TokenType::ASSIGN, "=", 1);
    Token t2 = Token(TokenType::NAME_IDENTIFIER, "x", 1);

    string t1String = ToString(t1);
    string t2String = ToString(t2);

    REQUIRE(t1String == "ASSIGN=1");
    REQUIRE(t2String == "NAME_IDENTIFIERx1");
}