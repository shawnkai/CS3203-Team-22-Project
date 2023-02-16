#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include "Token.h"
#include "Tokenizer.h"

bool Tokenizer::isLegalLetter(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}

bool Tokenizer::isLegalDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool Tokenizer::isWhiteSpace(char c) {
    return c == ' ';
}

bool Tokenizer::isStatementTerminal(char c) {
    return c == ';';
}

bool Tokenizer::isCurlyBracket(char c) {
    return c == '{' || c == '}';
}

bool Tokenizer::isRoundBracket(char c) {
    return c == '(' || c == ')';
}

bool Tokenizer::isConditionalChar(char c) {
    return c == '!' || c == '|' || c == '&';
}

bool Tokenizer::isConditionalExpression(std::string s) {
    return s == "!" || s == "||" || s == "&&";
}

bool Tokenizer::isRelationalChar(char c) {
    return c == '>' || c == '<' || c == '=' || c == '!';
}

bool Tokenizer::isAssignmentChar(char c) {
    return c == '=';
}

bool Tokenizer::isRelationalExpression(std::string s) {
    return s == ">" || s == "<" || s == ">=" || s == "<=" || s == "==" || s == "!=";
}

bool Tokenizer::isLegalArithmeticChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

Token Tokenizer::checkingAndGettingToken(char delimeter, TokenType type, std::string tokenId, std::string remainingLine,
                                         int lineNumber) {
    if (remainingLine.find_first_not_of(delimeter) == std::string::npos) {
        return Token(type, tokenId, lineNumber);
    }
    else {
        std::wstring::size_type pos = remainingLine.find_first_not_of(delimeter);
        if (isLegalLetter(remainingLine[pos]) &&
        (type == PROCEDURE || type == READ || type == PRINT || type == CALL)) {
            switch (type) {
                case PROCEDURE: return Token(PROCEDURE, tokenId, lineNumber);
                case READ: return Token(READ, tokenId, lineNumber);
                case PRINT: return Token(PRINT, tokenId, lineNumber);
                case CALL: return Token(CALL, tokenId, lineNumber);
                default : return Token(UNKNOWN, tokenId, lineNumber);
            }
        }
        if (remainingLine[pos] == '(' && (type == WHILE || (type == IF && tokenId == "if"))) {
            if (type == WHILE) {
                return Token(WHILE, tokenId, lineNumber);
            }
            else {
                return Token(IF, tokenId, lineNumber);
            }
        }
        if (remainingLine[pos] == '{' && (type == IF && (tokenId == "then" || tokenId == "else"))) {
            if (tokenId == "then") {
                return Token(IF, tokenId, lineNumber);
            }
            else {
                return Token(IF, tokenId, lineNumber);
            }
        }
        return Token(NAME_IDENTIFIER, tokenId, lineNumber);
    }
}

std::vector<Token> Tokenizer::handleKeyword(std::vector<Token> currentTokens, std::string candidateToken,
                                            std::string line, int charPos, int lineNumber) {
    std::string follows = line.substr(charPos);
    if (candidateToken == "procedure") {
        Token toAdd = checkingAndGettingToken(' ', PROCEDURE, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "read") {
        Token toAdd = checkingAndGettingToken(' ', READ, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "print") {
        Token toAdd = checkingAndGettingToken(' ', PRINT, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "while") {
        Token toAdd = checkingAndGettingToken(' ', WHILE, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "if") {
        prevIfLineNumberRecorder = lineNumber;
        Token toAdd = checkingAndGettingToken(' ', IF, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "then") {
        Token toAdd = checkingAndGettingToken(' ', IF, candidateToken, follows, prevIfLineNumberRecorder);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "else") {
        Token toAdd = checkingAndGettingToken(' ', IF, candidateToken, follows, prevIfLineNumberRecorder);
        currentTokens.push_back(toAdd);
    }
    else if (candidateToken == "call") {
        Token toAdd = checkingAndGettingToken(' ', CALL, candidateToken, follows, lineNumber);
        currentTokens.push_back(toAdd);
    }
    return currentTokens;
}

std::vector<Token> Tokenizer::tokenize(const char* fileName) {
    std::ifstream inputSimpleProgram(fileName);
    std::vector<Token> tokens;
    if (!inputSimpleProgram.is_open()) {
        std::cout << "inputFile not opened" << std::endl;
    }
    // currLineNum is initialised to 0 because procedure declaration line is not counted as a statement
    int currLineNum = 0;
    std::string currLine;
    while (std::getline(inputSimpleProgram, currLine)) {
        if (currLine.find("while") != std::string::npos
        || currLine.find("if") != std::string::npos
        || currLine.find(';') != std::string::npos) {
            currLineNum++;
        }
        int charPos = 0;
        while (charPos < currLine.length()) {
            std::string candidateToken;
            char charToProcess = currLine[charPos];
            if (isLegalLetter(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                while (charPos < currLine.length() &&
                (isLegalLetter(currLine[charPos]) || isLegalDigit(currLine[charPos]))) {
                    candidateToken.push_back(currLine[charPos]);
                    ++ charPos;
                }
                if (candidateToken == "procedure" || candidateToken == "read" || candidateToken == "print"
                || candidateToken == "while" || candidateToken == "if" || candidateToken == "then"
                || candidateToken == "else" || candidateToken == "call") {
                    tokens = handleKeyword(tokens, candidateToken, currLine, charPos,
                                           currLineNum);
                }
                else {
                    tokens.push_back(Token(NAME_IDENTIFIER, candidateToken,
                                               currLineNum));
                }
            }
            else if (isLegalDigit(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                while (isLegalDigit(currLine[charPos]) && charPos < currLine.length()) {
                    candidateToken.push_back(currLine[charPos]);
                    ++ charPos;
                }
                candidateToken = candidateToken.erase(0, std::min(candidateToken.find_first_not_of('0'),
                                                 candidateToken.size()-1));
                tokens.push_back(Token(INTEGER, candidateToken, currLineNum));
            }
            else if (isConditionalChar(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                if (isConditionalChar(currLine[charPos])) {
                    candidateToken.push_back(currLine[charPos]);
                    if (!(isConditionalExpression(candidateToken))) {
                        throw std::invalid_argument("Illegal SIMPLE Programme: Illegal token");
                    }
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                    ++ charPos;
                }
                else if (isAssignmentChar(currLine[charPos]) && charToProcess == '!') {
                    candidateToken.push_back(currLine[charPos]);
                    if (!(isRelationalExpression(candidateToken))) {
                        throw std::invalid_argument("Illegal SIMPLE Programme: Illegal token");
                    }
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                    ++ charPos;
                }
                else {
                    if (!(isConditionalExpression(candidateToken))) {
                        throw std::invalid_argument("Illegal SIMPLE Programme: Illegal token");
                    }
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                }
                continue;
            }
            else if (isRelationalChar(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                if (isRelationalChar(currLine[charPos])) {
                    candidateToken.push_back(currLine[charPos]);
                    if (!(isRelationalExpression(candidateToken))) {
                        throw std::invalid_argument("Illegal SIMPLE Programme: Illegal token");
                    }
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                    ++ charPos;
                }
                else {
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                }
                continue;
            }
            else if (isAssignmentChar(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                if (isAssignmentChar(currLine[charPos])) {
                    candidateToken.push_back(currLine[charPos]);
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                    ++ charPos;
                }
                else {
                    tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
                }
            }
            else if (isLegalArithmeticChar(charToProcess)) {
                candidateToken.push_back(charToProcess);
                ++ charPos;
                tokens.push_back(Token(OPERATOR, candidateToken, currLineNum));
            }
            else if (isWhiteSpace(charToProcess)) {
                ++ charPos;
            }
            else if (isStatementTerminal(charToProcess)) {
                ++ charPos;
                tokens.push_back(Token(STATEMENT_TERMINAL, ";", currLineNum));
            }
            else if (isCurlyBracket(charToProcess)) {
                ++ charPos;
                if (charToProcess == '{') {
                    tokens.push_back(Token(LEFT_CURLY_BRACKET, "{", currLineNum));
                }
                else {
                    tokens.push_back(Token(RIGHT_CURLY_BRACKET, "}", currLineNum));
                }
            }
            else if (isRoundBracket(charToProcess)) {
                ++ charPos;
                if (charToProcess == '(') {
                    tokens.push_back(Token(LEFT_ROUND_BRACKET, "(", currLineNum));
                }
                else {
                    tokens.push_back(Token(RIGHT_ROUND_BRACKET, ")", currLineNum));
                }
            }
            else {
                throw std::invalid_argument("Illegal SIMPLE Programme: Illegal token outside defined namespace");
            }
        }
    }
    return tokens;
}

//int main() {
//    const char* fileTest = "/Users/diwuyi/CLionProjects/spa-cp/Team22/Code22/src/spa/src/SP/SPtestFile_DoNotRemove.txt";
//    std::cout << "received file name" << fileTest << std::endl;
//    std::ifstream test(fileTest);
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