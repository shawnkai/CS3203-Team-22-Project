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
        exit(1);
    }
    REQUIRE(tokenList.size() == 7);
    REQUIRE(tokenList[0].type == TokenType::PROCEDURE);
    REQUIRE(tokenList[1].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::RIGHT_CURLY_BRACKET);
}

TEST_CASE("TestCase2_TokenizeWhileStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut2.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 35);
    REQUIRE(tokenList[3].type == TokenType::WHILE);
    REQUIRE(tokenList[6].type == TokenType::OPERATOR);
    REQUIRE(tokenList[10].type == TokenType::NAME_IDENTIFIER);
}

TEST_CASE("TestCase3_TokenizeIfStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut3.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 28);
    REQUIRE(tokenList[3].type == TokenType::IF);
    REQUIRE(tokenList[3].value == "if");
    REQUIRE(tokenList[9].type == TokenType::IF);
    REQUIRE(tokenList[9].value == "then");
    REQUIRE(tokenList[18].type == TokenType::IF);
    REQUIRE(tokenList[18].value == "else");
}

TEST_CASE("TestCase4_TokenizeReadPrintStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut4.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 16);
    REQUIRE(tokenList[3].type == TokenType::READ);
    REQUIRE(tokenList[4].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::READ);
    REQUIRE(tokenList[7].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[9].type == TokenType::PRINT);
    REQUIRE(tokenList[10].type == TokenType::NAME_IDENTIFIER);
}

TEST_CASE("TestCase5_TokenizeAssignStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut5.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 26);
    REQUIRE(tokenList[3].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[4].type == TokenType::OPERATOR);
    REQUIRE(tokenList[6].type == TokenType::LEFT_ROUND_BRACKET);
    REQUIRE(tokenList[7].type == TokenType::INTEGER);
    REQUIRE(tokenList[13].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[25].type == TokenType::RIGHT_CURLY_BRACKET);
}

TEST_CASE("TestCase6_TokenizeComplexSimpleSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut6.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 157);
    REQUIRE(tokenList[1].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::OPERATOR);
    REQUIRE(tokenList[10].type == TokenType::LEFT_ROUND_BRACKET);
    REQUIRE(tokenList[13].type == TokenType::INTEGER);
    REQUIRE(tokenList[16].type == TokenType::IF);
    REQUIRE(tokenList[150].type == TokenType::PRINT);
}

TEST_CASE("TestCase7_TokenizeIllegalSimpleSource_ShouldThrowException") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    bool isExceptionThrown = false;
#if __APPLE__
    relativePath = "SPTestingResources/SP_Tokenizer_ut7.txt";
#endif
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        isExceptionThrown = true;
    }
    REQUIRE(isExceptionThrown);
}
