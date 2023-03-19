#include "TestWrapper.h"

#include <vector>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Parser/TNode.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/SPDriver.h"
#include "SP/Parser/Parser.h"
#include <queue>
#include "PKB/PKB.h"
#include "QPS/Parser/Parser.h"
#include "QPS/Evaluator/Evaluator.h"
#include "QPS/Exceptions/Exceptions.h"

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

}

PKB pkb;

QueryEvaluator evaluator(pkb);

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
    QueryParser parser;
    size_t ind = query.find_last_of(';');
    string declaration = query.substr(0, ind + 1);
    string queryToExecute = query.substr(ind + 1, query.size() - ind);

    try {
        parser.parse(declaration);
        auto exp = parser.parse(queryToExecute);
        vector<string> exp_res = evaluator.evaluate(exp);
        for (const string& r : exp_res) {
            results.push_back(r);
        }
    } catch (SyntacticException& e) {
        results.emplace_back("SyntaxError");
    } catch (SemanticException& e) {
        results.emplace_back("SemanticError");
    }

}
