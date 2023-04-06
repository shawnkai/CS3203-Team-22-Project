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
    ParserFactory factory;
    auto parser = factory.createParser(TokenType::PROGRAM, tokenList, make_shared<int>(0));
    std::shared_ptr<TreeNode> result;
    try {
        result = parser->parse();
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
        ::exit(1);
    }
    if (result->children.empty()) {
        cout << "Null pointer returned, use debug mode to find out why" << endl;
    }
    std::queue<std::shared_ptr<TreeNode> > pendingToString;
    pendingToString.push(result);

    while (!pendingToString.empty()) {
        auto toProcess = pendingToString.front();
        pendingToString.pop();
        cout << ToString(*toProcess.get()) << endl;
        if (!toProcess->children.empty()) {
            auto childrenArr = (toProcess)->children;
            for (auto child : childrenArr) {
                pendingToString.push(child);
            }
        }
    }

    PKB pkbinstance = PKB();
    DesignExtractor designExtractor;
    //designExtractor.extractAbstraction(result, pkbinstance);

    vector<Cfg> controlFlowGraphs;
    for (auto procedure: result->children) {
        Cfg controlFlowGraph = Cfg(*procedure);
        controlFlowGraph.buildCfg(*procedure, -1);
        controlFlowGraphs.push_back(controlFlowGraph);
        pkbinstance.addControlFlowGraph(procedure->stringId, controlFlowGraph.basicBlock,
                                        controlFlowGraph.blockToStatement,
                                        controlFlowGraph.statementNumberToBlock,
                                        controlFlowGraph.blockGraph,
                                        controlFlowGraph.blockPointingBackward);
        cout << controlFlowGraph.toString() << endl;
    }
//        NextExtractor nextExtractor;
//        nextExtractor.extractAbstraction(controlFlowGraph.basicBlock, controlFlowGraph.blockToStatement, controlFlowGraph.statementNumberToBlock, controlFlowGraph.blockGraph, controlFlowGraph.blockPointingBackward, pkbinstance, procedure.stringId);

//    PKB pkbinstance = PKB();
//    DesignExtractor designExtractor;
//    designExtractor.extractAbstraction(result, pkbinstance);
//
//    vector<Cfg> controlFlowGraphs;
//    for (auto procedure: result.children) {
//        Cfg controlFlowGraph = Cfg(procedure);
//        controlFlowGraph.buildCfg(procedure, -1);
//        controlFlowGraphs.push_back(controlFlowGraph);
//        pkbinstance.addControlFlowGraph(procedure.stringId,controlFlowGraph.basicBlock,
//                                        controlFlowGraph.blockToStatement,
//                                        controlFlowGraph.statementNumberToBlock,
//                                        controlFlowGraph.blockGraph,
//                                        controlFlowGraph.blockPointingBackward);
//
//    }
//    for (auto graph: controlFlowGraphs) {
//        cout << graph.toString() << endl;
//    }
//
}