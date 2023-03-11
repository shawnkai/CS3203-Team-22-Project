//
// Created by Yi Zhang on 30/1/23.
//
#include "SP/Parser/TNode.h"
#include "SP/Parser/Parser.h"
#include "SP/Tokenizer/Tokenizer.h"
#include "catch.hpp"
#include <filesystem>

using namespace std;

TEST_CASE("TestCase1_ParseTokenListBasicSource_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    //base test 1 read and print
    tokens.push_back(Token(TokenType::READ, "read", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "x", 1));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 1));
    tokens.push_back(Token(TokenType::PRINT, "print", 2));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 2));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));

    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    REQUIRE(result.nodeType == TokenType::PROCEDURE);
    REQUIRE(result.children.size() == 1);
    REQUIRE(result.children[0].children.size() == 2);
}

TEST_CASE("TestCase2_ParseTokenListAssignStatement_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    //base test 2 assignment stmt
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "normsq", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centX", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centX", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centY", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centY", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "-", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 1));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    TNode stmtList = result.children[0];
    REQUIRE(stmtList.children.size() == 1);
    REQUIRE(stmtList.children[0].nodeType == TokenType::ASSIGN);
    REQUIRE(stmtList.children[0].children.size() == 2);

    TNode lhs = stmtList.children[0].children[0];
    REQUIRE(lhs.nodeType == TokenType::NAME_IDENTIFIER);

    TNode rhs = stmtList.children[0].children[1];
    REQUIRE(rhs.nodeType == TokenType::OPERATOR);
}

TEST_CASE("TestCase3_ParseTokenListWhileStatement_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    //base test 3 while stmt
    tokens.push_back(Token(TokenType::WHILE, "while", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "z", 1));
    tokens.push_back(Token(TokenType::OPERATOR, ">", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 1));
    tokens.push_back(Token(TokenType::INTEGER, "2", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::INTEGER, "3", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 1));
    tokens.push_back(Token(TokenType::INTEGER, "4", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "||", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "z", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "==", 1));
    tokens.push_back(Token(TokenType::INTEGER, "0", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "j", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
    tokens.push_back(Token(TokenType::INTEGER, "7", 2));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    TNode stmtList = result.children[0];
    REQUIRE(stmtList.children.size() == 1);

    TNode stmt = stmtList.children[0];
    REQUIRE(stmt.nodeType == TokenType::WHILE);
    REQUIRE(stmt.children.size() == 2);
    REQUIRE(stmt.children[0].nodeType == OPERATOR);

    TNode opNode = stmt.children[0];
    REQUIRE(opNode.stringId == "or");
    REQUIRE(stmt.children[1].nodeType == STATEMENT_LIST);
}

TEST_CASE("TestCase4_ParseTokenListWhileStatementExpr2_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    tokens.push_back(Token(TokenType::WHILE, "while", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 2));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 2));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 2));
    tokens.push_back(Token(TokenType::INTEGER, "1", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 2));
    tokens.push_back(Token(TokenType::INTEGER, "2", 2));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "*", 2));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 2));
    tokens.push_back(Token(TokenType::INTEGER, "3", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 2));
    tokens.push_back(Token(TokenType::INTEGER, "4", 2));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 2));
    tokens.push_back(Token(TokenType::INTEGER, "5", 2));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "%", 2));
    tokens.push_back(Token(TokenType::INTEGER, "6", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "/", 2));
    tokens.push_back(Token(TokenType::INTEGER, "7", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "==", 2));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "a", 0));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 2));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "j", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
    tokens.push_back(Token(TokenType::INTEGER, "7", 2));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    TNode stmtList = result.children[0];
    REQUIRE(stmtList.children.size() == 1);

    TNode stmt = stmtList.children[0];
    REQUIRE(stmt.nodeType == TokenType::WHILE);
    REQUIRE(stmt.children.size() == 2);
    REQUIRE(stmt.children[0].nodeType == OPERATOR);
    REQUIRE(stmt.children[0].stringId == "==");
}

TEST_CASE("TestCase5_ParseTokenListWhileStatementExpr3_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    //complex conditional expression
    tokens.push_back(Token(TokenType::WHILE, "while", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::OPERATOR, ">=", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "%", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::INTEGER, "2", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "-", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "j", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
    tokens.push_back(Token(TokenType::INTEGER, "7", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "%", 1));
    tokens.push_back(Token(TokenType::INTEGER, "2", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "+", 1));
    tokens.push_back(Token(TokenType::INTEGER, "3", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
    tokens.push_back(Token(TokenType::INTEGER, "4", 1));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    TNode stmtList = result.children[0];
    REQUIRE(stmtList.children.size() == 1);

    TNode whileNode = stmtList.children[0];
    TNode condNode = whileNode.children[0];
    REQUIRE(condNode.nodeType == TokenType::OPERATOR);
    REQUIRE(condNode.children[1].stringId == "%");
}

TEST_CASE("TestCase6_ParseTokenListIfStatement_ShouldSuccess") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    //base test 4 if stmt
    tokens.push_back(Token(TokenType::IF, "if", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "!", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 1));
    tokens.push_back(Token(TokenType::OPERATOR, ">", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::IF, "then", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
    tokens.push_back(Token(TokenType::INTEGER, "1", 2));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    tokens.push_back(Token(TokenType::IF, "else", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 2));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 3));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 3));
    tokens.push_back(Token(TokenType::INTEGER, "2", 3));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 3));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));

    Parser ps = Parser(tokens);
    TNode result;
    try {
        result = ps.Parse();
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    TNode stmtList = result.children[0];
    REQUIRE(stmtList.children.size() == 1);

    TNode stmt = stmtList.children[0];
    REQUIRE(stmt.nodeType == TokenType::IF);
    REQUIRE(stmt.children.size() == 3);
    REQUIRE(stmt.children[0].nodeType == OPERATOR);
    REQUIRE(stmt.children[0].stringId == "neg");
    REQUIRE(stmt.children[1].nodeType == STATEMENT_LIST);
    REQUIRE(stmt.children[1].stringId == "then");
    REQUIRE(stmt.children[2].nodeType == STATEMENT_LIST);
    REQUIRE(stmt.children[2].stringId == "else");

    TNode negationNode = stmt.children[0];
    REQUIRE(negationNode.children.size() == 1);

    TNode greaterThanNode = negationNode.children[0];
    REQUIRE(greaterThanNode.stringId == ">");
}

TEST_CASE("TestCase7_ParseBasicSimpleSource_ShouldSuccess") {
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
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(result.nodeType == TokenType::PROCEDURE);
    REQUIRE(result.children.size() == 1);
    REQUIRE(result.children[0].children.size() == 1);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase8_ParseWhileStmtSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut8.txt";
    string code = "procedure Example {\n"
                  "  while (i!=0) {\n"
                  "    x = x - 1;\n"
                  "    z = z + x + i;\n"
                  "    read print;\n"
                  "    i = i - 1; }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();
    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    auto whileStmt = node.children[0];
    REQUIRE(whileStmt.nodeType == TokenType::WHILE);
    REQUIRE(whileStmt.children.size() == 2);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase9_ParseIfStmtSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut9.txt";

    string code = "procedure Example {\n"
                  "    if (x>=1) then {\n"
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
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);

    auto node2 = node.children[0];
    REQUIRE(node2.nodeType == TokenType::IF);
    REQUIRE(node2.children.size() == 3);

    auto cond = node2.children[0];
    REQUIRE(cond.nodeType == TokenType::OPERATOR);
    REQUIRE(cond.stringId == ">=");
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase10_ParseReadPrintStmtSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut10.txt";

    string code = "procedure compute {\n"
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
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 4);
    auto node2 = node.children[3];
    REQUIRE(node2.nodeType == TokenType::PRINT);
    REQUIRE(node2.children.size() == 1);
    auto node3 = node2.children[0];
    REQUIRE(node3.nodeType == TokenType::NAME_IDENTIFIER);
    REQUIRE(node3.stringId == "call");
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase11_ParseAssignStmtSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut11.txt";

    string code = "procedure compute {\n"
                  "    x = ((1 + 2) * (a + 4) + 5) % 6 / 7 ;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 1);
    auto node2 = node.children[0];
    REQUIRE(node2.nodeType == TokenType::ASSIGN);
    REQUIRE(node2.children.size() == 2);
    auto node3 = node2.children[1];
    REQUIRE(node3.nodeType == TokenType::OPERATOR);
    REQUIRE(node3.stringId == "/");
    REQUIRE(filesystem::remove(relativePath)) ;
}

TEST_CASE("TestCase12_ParseIfWhileCombinedMix1_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut12.txt";

    string code = "procedure p {\n"
                  "  if (x<0) then {\n"
                  "    print a;\n"
                  "    while (i>0) {\n"
                  "      x = z * 3 + 2 * y;\n"
                  "      read q;\n"
                  "      i = i - 1; }\n"
                  "    x = x + 1;\n"
                  "    z = x + z; }\n"
                  "  else {\n"
                  "    z = 1; }\n"
                  "  z = z + x + i; }";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 2);
    auto node2 = node.children[0];
    auto node3 = node.children[1];
    REQUIRE(node2.nodeType == TokenType::IF);
    REQUIRE((node3.nodeType == TokenType::ASSIGN));
    REQUIRE(node2.children.size() == 3);
    auto node4 = node2.children[1];
    REQUIRE(node4.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node4.children.size() == 4);
    auto node5 = node4.children[1];
    REQUIRE(node5.nodeType == TokenType::WHILE);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase13_ParseIfWhileCombinedMix2_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut13.txt";

    string code = "procedure Example {\n"
                  "  x = 2;\n"
                  "  z = 3;\n"
                  "  i = 5;\n"
                  "  while (i!=0) {\n"
                  "    x = x - 1;\n"
                  "    if (x==1) then {\n"
                  "      z = x + 1; }\n"
                  "    else {\n"
                  "      y = z + x;\n"
                  "    }\n"
                  "  }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 4);

    auto node2 = node.children[3];
    REQUIRE(node2.nodeType == TokenType::WHILE);

    auto node3 = node2.children[1];
    REQUIRE(node3.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node3.children.size() == 2);
    REQUIRE(node3.children[1].nodeType == TokenType::IF);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase14_ParseIfWhileCombinedMix3_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut14.txt";

    string code = "procedure Example {\n"
                  "  x = 2;\n"
                  "  z = 3;\n"
                  "  while (i!=0) {\n"
                  "    if (x==1) then {\n"
                  "      z = x + 1; }\n"
                  "    else {\n"
                  "      y = z + x;\n"
                  "    }\n"
                  "    x = x - 1;\n"
                  "  }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 3);

    auto node2 = node.children[2];
    REQUIRE(node2.nodeType == TokenType::WHILE);

    auto node3 = node2.children[1];
    REQUIRE(node3.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node3.children.size() == 2);
    REQUIRE(node3.children[0].nodeType == TokenType::IF);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase15_ParseDeepNestingSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut15.txt";

    string code = "procedure Example {\n"
                  "  x = 2;\n"
                  "  z = 3;\n"
                  "  while (i!=0) {\n"
                  "    if (x==1) then {\n"
                  "      z = x + 1;\n"
                  "      while (a < 9) {\n"
                  "        while(b > 7) {\n"
                  "          while (c == 8) {\n"
                  "            while (maz != 10) {\n"
                  "              while (i >= 0) {\n"
                  "                print here123;\n"
                  "              }\n"
                  "            }\n"
                  "          }\n"
                  "        }\n"
                  "      }\n"
                  "    } else {\n"
                  "        y = z + x;\n"
                  "    }\n"
                  "  }\n"
                  "  x = x - 1;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 4);
    auto node2 = node.children[2];
    auto node3 = node2.children[1].children[0];
    auto node4 = node3.children[1].children[1];
    auto node5 = node4.children[1].children[0];
    auto node6 = node5.children[1].children[0];
    auto node7 = node6.children[1].children[0];
    auto node8 = node7.children[1].children[0];
    auto node9 = node8.children[1].children[0];
    REQUIRE(node9.nodeType == TokenType::PRINT);
    auto node10 = node9.children[0];
    REQUIRE(node10.stringId == "here123");
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase16_ParseComplexConditionalStmt_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut16.txt";

    string code = "procedure Example {\n"
                  " while (!(!((z > (1+2) * (3+4)) && ((z - 3) <= 9) ))) {\n"
                  "  j = 7 ;\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 1);
    auto node2 = node.children[0].children[0];
    REQUIRE(node2.stringId == "neg");
    auto node3 = node2.children[0];
    REQUIRE(node3.stringId == "neg");
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase17_ParseComplexConditionalStmtVariation2_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut17.txt";

    string code = "procedure Example {\n"
                  " while ( (b == 9) || ( ((z > (1+2) * (3+4)) && ((z - 3) <= 9) ) && (a == 1))) {\n"
                  "  j = 7 ;\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 1);
    auto node2 = node.children[0].children[0];
    REQUIRE(node2.stringId == "or");
    REQUIRE(node2.children.size() == 2);
    auto node3 = node2.children[1];
    REQUIRE(node3.stringId == "and");
    REQUIRE(node3.children.size() == 2);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase18_ParseGrandSimpleSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut18.txt";

    string code = "procedure Example {\n"
                  " x = 2;\n"
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
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    auto node = result.children[0];
    REQUIRE(node.nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(node.children.size() == 2);

    auto node2 = node.children[1];
    auto node3 = node2.children[1].children[0];
    REQUIRE(node3.nodeType == TokenType::IF);
    REQUIRE(node3.children.size() == 3);
    REQUIRE(node3.children[0].stringId == ">");
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase19_ParseIllegalToken_ShouldThrowException") {
    vector<Token> tokens;
    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
    tokens.push_back(Token(TokenType::IF, "if", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::OPERATOR, "!", 1));
    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 1));
    tokens.push_back(Token(TokenType::OPERATOR, ">", 1));
    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
    tokens.push_back(Token(TokenType::IF, "then", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
    //Token NOT recognized
    tokens.push_back(Token(TokenType::UNKNOWN, "!!!", 1));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 2));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
    tokens.push_back(Token(TokenType::INTEGER, "1", 2));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
    tokens.push_back(Token(TokenType::IF, "else", 1));
    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 2));
    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 3));
    tokens.push_back(Token(TokenType::OPERATOR, "=", 3));
    tokens.push_back(Token(TokenType::INTEGER, "1", 3));
    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 3));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));
    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));
    Parser ps = Parser(tokens);
    TNode result;
    bool isThrownException = false;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        isThrownException = true;
    }

    REQUIRE(isThrownException);
}

TEST_CASE("TestCase20_ParseIllegalGrammar_ShouldThrowException") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut19.txt";

    string code = "procedure Example {\n"
                  " x = 2;;;\n"
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
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    bool isThrownException = false;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        isThrownException = true;
    }

    REQUIRE(isThrownException);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase21_ParseTanglingTokenOutsideProcedure_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath = "sp_ut21.txt";

    string code = "procedure Example {\n"
                  " x = 2;\n"
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
                  "} random ; staff 123";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    REQUIRE(result.nodeType == TokenType::PROCEDURE);
    REQUIRE(result.children.size() == 1);
    REQUIRE(result.children[0].nodeType == TokenType::STATEMENT_LIST);
    REQUIRE(filesystem::remove(relativePath));
}

TEST_CASE("TestCase22_ParseLongProcedure_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut22.txt";

    string code = "procedure TestFollows {\n"
                  " x = 1;\n"
                  " print y;\n"
                  " while (z>2) {\n"
                  "   read z;\n"
                  "   print k;\n"
                  "   if (a < 2) then {\n"
                  "     read y;\n"
                  "   } else {\n"
                  "     k = k + 1;\n"
                  "     while (b <= 6) {\n"
                  "       read a;\n"
                  "       while (c > 3) {\n"
                  "         if (d > a) then {\n"
                  "           z = 1;\n"
                  "         } else {\n"
                  "           print z;\n"
                  "           read b;\n"
                  "         }\n"
                  "       }\n"
                  "     }\n"
                  "   }\n"
                  "   y = a - 1;\n"
                  " }\n"
                  "  if (z > 1) then {\n"
                  "    read k;\n"
                  "  } else {\n"
                  "    while (x > 2) {\n"
                  "      z = 5;\n"
                  "    }\n"
                  "    while (y <= 9) {\n"
                  "      print y;\n"
                  "      print x;\n"
                  "      if (a > 5) then {\n"
                  "         while (a >6) {\n"
                  "            a = a + 1;\n"
                  "            print a;\n"
                  "            while (z > 3) {\n"
                  "               read z;\n"
                  "            }\n"
                  "         }\n"
                  "       } else {\n"
                  "       }\n"
                  "     }  \n"
                  "  }\n"
                  " read z;\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    REQUIRE(result.nodeType == TokenType::PROGRAM);
}
