/* example in mind:
 * procedure main {
 * read x;
 * }
 */
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Token.h"

class Tokenizer {
private:
    std::ifstream inputSimpleProgram;
    std::vector<Token> tokens;
    std::map<std::string, TokenType> keyWordsMap;
    int currLineNum;

    void insertPredefined() {
        keyWordsMap["procedure"] = PROCEDURE;
        keyWordsMap["read"] = READ;
    }

    bool isLegalLetter(char c) {
        if (c >= 'A' && c <= 'Z') {
            return true;
        }
        if (c >= 'a' && c <= 'z') {
            return true;
        }
        return false;
    }

    bool isWhiteSpace(char c) {
        return c == ' ';
    }

    bool isStatementTerminal(char c) {
        return c == ';';
    }

    bool isCurlyBracket(char c) {
        return c == '{' || c == '}';
    }

    bool isRoundBracket(char c) {
        return c == '(' || c == ')';
    }

public:
    explicit Tokenizer(const char* fileName) {
        inputSimpleProgram.open(fileName);
        currLineNum = 0;
    }

    ~Tokenizer() {
        inputSimpleProgram.close();
    }

    std::vector<Token> tokenize() {
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
                        tokens.push_back(Token{PROCEDURE, "procedure", currLineNum});
                    }
                    else if (candidateToken == "read") {
                        tokens.push_back(Token{READ, "read", currLineNum});
                    }
                    else {
                        tokens.push_back(Token{NAME_IDENTIFIER, candidateToken,
                                               currLineNum});
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
                        tokens.push_back(Token{LEFT_CURLY_BRACKET, "{", currLineNum});
                    }
                    else {
                        tokens.push_back(Token{RIGHT_CURLY_BRACKET, "}", currLineNum});
                    }
                }
            }
        }
        return tokens;
    }
};
