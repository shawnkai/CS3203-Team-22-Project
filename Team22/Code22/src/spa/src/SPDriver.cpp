// main {'iostream' tokens =  Tokenizer.tokenize(); AST ast = Parser.parse(tokens); Designs design = DE.extract(ast);
// populatePBK(design)}
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

void SPDriver::parseSimpleProgram() {
	try {
		TNode var;
		var.nodeType = TokenType::NAME_IDENTIFIER;
		var.stringId = "x";
		var.stmtNumber = 2;
		var.children = std::vector<TNode>(0);

		TNode read;
		read.nodeType = TokenType::READ;
		read.stringId = "read";
		read.stmtNumber = 2;
		read.children = std::vector<TNode>{ var };

		TNode stmtlist;
		stmtlist.nodeType = TokenType::STATEMENT_LIST;
		stmtlist.stringId = "stmtlist";
		stmtlist.stmtNumber = 1;
		stmtlist.children = std::vector<TNode>{ read };

		TNode root;
		root.nodeType = TokenType::PROCEDURE;
		root.stringId = "main";
		root.stmtNumber = 0;
		root.children = std::vector<TNode>{ stmtlist };

		DesignExtractor designextractor;
		designextractor.extractAbstraction(root);

		designextractor.extractEntity(root);
	}
	catch (std::logic_error& error) {
		        exit(1);
		    }
}