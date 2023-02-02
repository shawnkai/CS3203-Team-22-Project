/* example in mind:
 * procedure main {
 * read x;
 * }
 */
//#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Token.h"

class Tokenizer {
private:
    std::map<std::string, TokenType> keyWordsMap;
    //static int currLineNum;

    void insertPredefined() {
        keyWordsMap["procedure"] = PROCEDURE;
        keyWordsMap["read"] = READ;
    }

    static bool isLegalLetter(char c) {
        if (c >= 'A' && c <= 'Z') {
            return true;
        }
        if (c >= 'a' && c <= 'z') {
            return true;
        }
        return false;
    }

    static bool isWhiteSpace(char c) {
        return c == ' ';
    }

    static bool isStatementTerminal(char c) {
        return c == ';';
    }

    static bool isCurlyBracket(char c) {
        return c == '{' || c == '}';
    }

    static bool isRoundBracket(char c) {
        return c == '(' || c == ')';
    }

public:

//    static std::ifstream inputSimpleProgram;
//    static std::vector<Token> tokens;

//    explicit Tokenizer(const char* fileName) {
//        inputSimpleProgram.open(fileName);
//    }
//
//    ~Tokenizer() {
//        inputSimpleProgram.close();
//    }

    std::vector<Token> tokenize(const char* fileName) {
        std::ifstream inputSimpleProgram("/Users/diwuyi/CLionProjects/spa-cp/Team22/Code22/src/spa/src/SPtestFile_DoNotRemove.txt");
        std::vector<Token> tokens;
        //inputSimpleProgram.open(fileName);
        if (!inputSimpleProgram.is_open()) {
            std::cout << "testFile not opened" << std::endl;
        }
        int currLineNum = 0;
        std::string currLine;
        // getline require pass by reference
        while (std::getline(inputSimpleProgram, currLine)) {
            ++ currLineNum;
            int charPos = 0;
            while (charPos < currLine.length()) {
                std::string candidateToken;
                char charToProcess = currLine[charPos];
                if (isLegalLetter(charToProcess)) {
                    candidateToken.push_back(charToProcess);
                    ++ charPos;
                    while (charPos < currLine.length() && isLegalLetter(currLine[charPos])) {
                        candidateToken.push_back(currLine[charPos]);
                        ++ charPos;
                    }
                    if (candidateToken == "procedure") {
                        tokens.push_back(Token(PROCEDURE, "procedure", currLineNum));
                    }
                    else if (candidateToken == "read") {
                        tokens.push_back(Token(READ, "read", currLineNum));
                    }
                    else {
                        tokens.push_back(Token(NAME_IDENTIFIER, candidateToken,
                                               currLineNum));
                    }
                }
                if (isWhiteSpace(charToProcess)) {
                    charPos ++;
                }
                if (isStatementTerminal(charToProcess)) {
                    charPos ++;
                    tokens.push_back(Token(STATEMENT_TERMINAL, ";", currLineNum));
                }
                if (isCurlyBracket(charToProcess)) {
                    charPos ++;
                    if (charToProcess == '{') {
                        tokens.push_back(Token(LEFT_CURLY_BRACKET, "{", currLineNum));
                    }
                    else {
                        tokens.push_back(Token(RIGHT_CURLY_BRACKET, "}", currLineNum));
                    }
                }
            }
        }
        return tokens;
    }
};

//int main() {
//    const char* fileTest = "SPtestFile_DoNotRemove.txt";
//    std::cout << "received file name" << fileTest << std::endl;
//    std::ifstream test("/Users/diwuyi/CLionProjects/spa-cp/Team22/Code22/src/spa/src/SPtestFile_DoNotRemove.txt");
//    if (test.is_open()) {
//        std::cout << "file opened" << std::endl;
//    }
//    Tokenizer tokenizer;
//    const std::vector<Token> tokens = tokenizer.tokenize(fileTest);
//    std::cout << "execution of tokenizer done" << std::endl;
//    //driver.parseSimpleProgram(fileTest);
//    for (Token token: tokens) {
//            std::cout << "Token" << ToString(token) << std::endl;
//        }
//    return 0;
//};