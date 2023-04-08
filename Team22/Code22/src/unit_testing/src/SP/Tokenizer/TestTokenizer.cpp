//
// Created by Yi Zhang on 14/2/23.
//
#include "SP/Tokenizer/Tokenizer.h"
#include "catch.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


using namespace std;

TEST_CASE("TestCase1_TokenizeSmallestProcedure_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut1.txt";
    string code = "procedure main {\n"
                  "    read x;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 7);
    REQUIRE(tokenList[0].type == TokenType::PROCEDURE);
    REQUIRE(tokenList[1].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::RIGHT_CURLY_BRACKET);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase2_TokenizeWhileStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut2.txt";
    string code = "procedure Example {\n"
                  "  while (i!=0) {\n"
                  "    x = x - 1;\n"
                  "    z = z + x + i;\n"
                  "    call q;\n"
                  "    i = i - 1; }\n"
                  " }";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 35);
    REQUIRE(tokenList[3].type == TokenType::WHILE);
    REQUIRE(tokenList[6].type == TokenType::OPERATOR);
    REQUIRE(tokenList[10].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase3_TokenizeIfStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut3.txt";

    string code = "procedure Example {\n"
                  "    if (x==1) then {\n"
                  "      z = x + 1; }\n"
                  "    else {\n"
                  "      y = z + x; }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
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
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase4_TokenizeReadPrintStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut4.txt";

    string code = "procedure main {\n"
                  "    read x;\n"
                  "    read call;\n"
                  "    print read;\n"
                  "    print call;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
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
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase5_TokenizeAssignStatement_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut5.txt";

    string code = "procedure main {\n"
                  "    x = ((1 + 2) * (a + 4) + 5) % 6 / 7 ;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
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
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase6_TokenizeComplexSimpleSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut6.txt";

    string code = "procedure Example {\n"
                  " x = 2 % 1;\n"
                  " while (i!=0) {\n"
                  "   if (x > 1) then {\n"
                  "     z = x + 1; }\n"
                  "   else {\n"
                  "     y = z + x;\n"
                  "     if (x >= 5) then {\n"
                  "        z = x + 1;\n"
                  "        while ( x < 10) {\n"
                  "           x = x - 1;\n"
                  "           while ((x <= 9) || ((z % 2) == 1)) {\n"
                  "             anx = 1;\n"
                  "             if (z == 1) then {\n"
                  "               z = 2;\n"
                  "             } else {\n"
                  "               z = 3;\n"
                  "               while (!(!(j < 0))) {\n"
                  "                 j = ((1 + 2) * (3 + 4) + 5) % 6 / 7 ;\n"
                  "               }\n"
                  "             }\n"
                  "           }\n"
                  "        }\n"
                  "     }\n"
                  "     else {\n"
                  "       print x;\n"
                  "     }\n"
                  "   }\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
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
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase7_TokenizeIllegalSimpleSource_ShouldThrowException") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    bool isExceptionThrown = false;

    relativePath = "SP_ut7.txt";

    string code = "procedure Example {\n"
                  " x = 2 % @ ;\n"
                  " while (i!=0) {\n"
                  "   if (x > 1) then {\n"
                  "     z = x + 1; }\n"
                  "   else {\n"
                  "     y = z + x;\n"
                  "     if (x >= 5) then {\n"
                  "        z = x + 1;\n"
                  "        while ( x < 10) {\n"
                  "           x = x - 1;\n"
                  "           while ((x <= 9) || ((z % 2) == 1)) {\n"
                  "             anx = 1;\n"
                  "             if (z == 1) then {\n"
                  "               z = 2;\n"
                  "             } else {\n"
                  "               z = 3;\n"
                  "               while (!(!(j < 0))) {\n"
                  "                 j = ((1 + 2) * (3 + 4) + 5) % 6 / 7 ;\n"
                  "               }\n"
                  "             }\n"
                  "           }\n"
                  "        }\n"
                  "     }\n"
                  "     else {\n"
                  "       print x;\n"
                  "     }\n"
                  "   }\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
        isExceptionThrown = true;
    }
    REQUIRE(isExceptionThrown);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase8_TokenizeProcedureWithTab_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut8.txt";
    string code = "procedure main {\n"
                  "\tread x;\n"
                  "\t }";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(tokenList.size() == 7);
    REQUIRE(tokenList[0].type == TokenType::PROCEDURE);
    REQUIRE(tokenList[1].type == TokenType::NAME_IDENTIFIER);
    REQUIRE(tokenList[6].type == TokenType::RIGHT_CURLY_BRACKET);
    REQUIRE(filesystem::remove(relativePath));
}
