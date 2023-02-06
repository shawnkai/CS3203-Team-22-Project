#include "TestWrapper.h"

#include <vector>
#include <Tokenizer.h>
#include <TNode.h>
#include <DesignExtractor.h>
#include <SPDriver.h>
#include <Parser.h>
#include <queue>
#include <PKB/PKB.h>

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

    Tokenizer tokenizer = Tokenizer();
    auto tokenList = tokenizer.tokenize("Sample_source.txt");
    std::cout << "execution of tokenizer done" << std::endl;
    //driver.parseSimpleProgram(fileTest);
    for (Token token: tokenList) {
            std::cout << "Token" << ToString(token) << std::endl;
        }
    Parser testParser = Parser(tokenList);
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
//  SPDriver class not in use for now
//	SPDriver spdriver;
//	spdriver.parseSimpleProgram();
    DesignExtractor designExtractor;
    designExtractor.extractAbstraction(result);
    designExtractor.extractEntity(result);

    PKB pkbinstance = PKB();
    
    cout << pkbinstance.getDesignEntity("VARIABLE", "x").toString() << endl;
    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "x")).toString() << endl;
    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("READ", "x")).toString() << endl;

}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.


}
