#include "TestWrapper.h"

#include <vector>
//#include <Tokenizer.h>
#include <TNode.h>
#include <DesignExtractor.h>
#include <SPDriver.h>
#include <Parser.h>
#include <queue>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
    /*const std::vector<Token> tokens = Tokenizer::tokenize("SPtestFile_DoNotRemove.txt");
    for (Token token : tokens) {
        std::cout << "Token" << ToString(token) << std::endl;
    }*/
	vector<Token> testList;
    Token t1 = Token(TokenType::PROCEDURE, "procedure", 0);
    Token t2 = Token(TokenType::NAME_IDENTIFIER, "main", 0);
    Token t3 = Token(TokenType::LEFT_CURLY_BRACKET, "{", 0);
    Token t4 = Token(TokenType::READ, "read", 1);
    Token t5 = Token(TokenType::NAME_IDENTIFIER, "x", 1);
    Token t6 = Token(TokenType::STATEMENT_TERMINAL, ";", 1);
	Token t7 = Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2);
    testList.push_back(t1);
    testList.push_back(t2);
    testList.push_back(t3);
    testList.push_back(t4);
    testList.push_back(t5);
    testList.push_back(t6);
    testList.push_back(t7);
    Parser testParser = Parser(testList);

    TNode result = testParser.Parse();
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
            for (TNode child: childrenArr) {
                pendingToString.push(child);
            }
        }
    }
	/*TNode var;
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
	designextractor.extractAbstraction(root);*/

	SPDriver spdriver;
	spdriver.parseSimpleProgram();

}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.


}
