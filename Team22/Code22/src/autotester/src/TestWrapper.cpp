#include "TestWrapper.h"

#include <vector>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Parser/TNode.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/SPDriver.h"
#include "SP/Parser/Parser.h"
#include <queue>
#include "PKB/PKB.h"
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
    SPDriver driver;
    driver.parseSimpleProgram(filename);
    PKB pkbinstance = PKB();
    cout << pkbinstance.getDesignEntity("VARIABLE", "x").toString() << endl;
    cout << pkbinstance.getDesignEntity("IF", "if").toString() << endl;
    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "x")).toString() << endl;
    cout << pkbinstance.getDesignAbstraction("MODIFIES", make_tuple("WHILE", "x")).toString() << endl;
    cout << pkbinstance.getDesignAbstraction("USES", make_tuple("IF", "z")).toString() << endl;
    cout << pkbinstance.getDesignAbstraction("USES", make_tuple("ASSIGNMENT", "a")).toString() << endl;


}

//QueryParser parser;
//PKB pkb;

//QueryEvaluator evaluator(pkb);

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
