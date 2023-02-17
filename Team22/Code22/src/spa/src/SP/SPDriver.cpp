#include <vector>
#include <iostream>
#include "SPDriver.h"
//#include "Tokenizer.h"
//#include "TNode.h"//added
//#include "DesignExtractor.h" //added

SPDriver::SPDriver() {}

/*void SPDriver::parseSimpleProgram(const char* fileName) {
    try {
        //Tokenizer spTokenizer(fileName);
        const std::vector<Token> tokens = Tokenizer::tokenize(fileName);
        for (Token token: tokens) {
           std::cout << "Token" << ToString(token) << std::endl;
        }
    }
    catch (std::logic_error &error) {
        exit(1);
    }
}*/

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
    //driver.parseSimpleProgram(fileTest);
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

    DesignExtractor designExtractor;
    designExtractor.extractAbstraction(result);
};