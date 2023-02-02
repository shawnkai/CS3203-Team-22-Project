// main {'iostream' tokens =  Tokenizer.tokenize(); AST ast = Parser.parse(tokens); Designs design = DE.extract(ast);
// populatePBK(design)}
#include <vector>
#include <iostream>
#include "SPDriver.h"
#include "Tokenizer.h"

SPDriver::SPDriver() {}

//void SPDriver::parseSimpleProgram(const char* fileName) {
//    try {
//        //Tokenizer spTokenizer(fileName);
//        const std::vector<Token> tokens = Tokenizer::tokenize(fileName);
//        for (Token token: tokens) {
//            std::cout << "Token" << ToString(token) << std::endl;
//        }
//    }
//    catch (std::logic_error &error) {
//        exit(1);
//    }
//}

