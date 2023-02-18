//
// Created by Yi Zhang on 14/2/23.
//
#include "SP/Tokenizer/Tokenizer.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "catch.hpp"


using namespace std;

//NOTE: This test cases' relative path is written for a MAC OS machine, it will break on a Windows Machine.
//Windows developer, please fill in the relative path when you run the unit tests.
TEST_CASE("TestCase1_TokenizeSmallestProcedure_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut1.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    REQUIRE(tokenList.size() == 7);
    REQUIRE(tokenList[0].type == TokenType::PROCEDURE);
    REQUIRE(tokenList[1].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::RIGHT_CURLY_BRACKET);
}

TEST_CASE("TestCase2_TokenizeWhileStatement_ShouldSuccess") {

}

TEST_CASE("TestCase3_TokenizeIfStatement_ShouldSuccess") {

}

TEST_CASE("TestCase4_TokenizeReadPrintStatement_ShouldSuccess") {

}

TEST_CASE("TestCase5_TokenizeIfStatement_ShouldSuccess") {

}
