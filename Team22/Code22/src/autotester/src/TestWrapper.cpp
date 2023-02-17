#include "TestWrapper.h"

#include <vector>
#include "SP/Tokenizer.h"
#include "SP/TNode.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/SPDriver.h"
#include "SP/Parser.h"
#include <queue>
#include <PKB/PKB.h>
#include "QPS/Parser.h"
#include "QPS/Evaluator.h"

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
    Tokenizer tokenizer = Tokenizer();
    std::vector<Token> tokenList;
    try {
        tokenList = tokenizer.tokenize(filename.c_str());
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
        ::exit(1);
    }
    std::cout << "execution of tokenizer done" << std::endl;
    //driver.parseSimpleProgram(fileTest);
    for (Token token: tokenList) {
            std::cout << "Token" << ToString(token) << std::endl;
        }
    Parser testParser = Parser(tokenList);
    TNode result;
    try {
        result = testParser.Parse();
    } catch (std::invalid_argument& e) {
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
            for (TNode child: childrenArr) {
                pendingToString.push(child);
            }
        }
    }
    
    DesignExtractor designExtractor;
    designExtractor.extractAbstraction(result);
////  SPDriver class not in use for now
////	SPDriver spdriver;
////	spdriver.parseSimpleProgram();
//    DesignExtractor designExtractor;
//    designExtractor.extractAbstraction(result);
//    designExtractor.extractEntity(result);
//
//    PKB pkbinstance = PKB();
//
//    cout << pkbinstance.getDesignEntity("VARIABLE", "x").toString() << endl;
//    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "x")).toString() << endl;
//    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("READ", "x")).toString() << endl;

}

QueryParser parser;
PKB pkb;

QueryEvaluator evaluator(pkb);

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
//      size_t ind = query.find_last_of(';');
//      string declaration = query.substr(0, ind + 1);
//      string queryToExecute = query.substr(ind + 1, query.size() - ind);
//
//      parser.parse(declaration);
//
//      auto exp = parser.parse(queryToExecute);
//      string exp_res = evaluator.evaluate(exp);
//      string res_to_add;
//      for (auto c : exp_res) {
//          if (c == ',') {
//              results.push_back(res_to_add);
//              res_to_add.clear();
//          } else if (c != ' ') {
//              res_to_add.push_back(c);
//          }
//      }
//      if (!res_to_add.empty()) {
//          results.push_back(res_to_add);
//      }
}
