#include <vector>
#include <iostream>
#include "SPDriver.h"

/**
 * Creates an instance of SPDriver.
 */
SPDriver::SPDriver() {}

/**
 * Parses the SIMPLE program and adds the abstractions and entities into the Program
 * Knowledge Base.
 *
 * @param filename The filename of the SIMPLE program.
 */
void SPDriver::parseSimpleProgram(std::string filename) {
    Tokenizer tokenizer = Tokenizer();
    std::vector<Token> tokenList;
    try {
        tokenList = tokenizer.tokenize(filename.c_str());
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
        ::exit(1);
    }
    std::cout << "execution of tokenizer done" << std::endl;
    for (Token token : tokenList) {
        std::cout << "Token" << ToString(token) << std::endl;
    }
    Parser testParser = Parser(tokenList);
    TNode result;
    try {
        result = testParser.Parse();
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
        ::exit(1);
    }
    if (result.children.empty()) {
        cout << "Null pointer returned, use debug mode to find out why" << endl;
    }
    std::queue<TNode> pendingToString;
    pendingToString.push(result);
    while (!pendingToString.empty()) {
        auto toProcess = pendingToString.front();
        pendingToString.pop();
        cout << ToString(toProcess) << endl;
        if (!toProcess.children.empty()) {
            auto childrenArr = (toProcess).children;
            for (TNode child : childrenArr) {
                pendingToString.push(child);
            }
        }
    }
    PKB pkbinstance = PKB();
    DesignExtractor designExtractor;
    designExtractor.extractAbstraction(result, pkbinstance);
}