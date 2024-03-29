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
void SPDriver::parseSimpleProgram(const std::string& filename) {
    Tokenizer tokenizer = Tokenizer();
    std::vector<Token> tokenList;
    ParserFactory factory;
    TNode result;

    try {
        tokenList = tokenizer.tokenize(filename.c_str());
        auto parser = factory.createParser(TokenType::PROGRAM, tokenList, make_shared<int>(0));
        result = parser->parse();
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
        ::exit(1);
    }

    std::cout << "execution of tokenizer and parser done, logging tokens and ast" << std::endl;
    for (const Token& token : tokenList) {
        std::cout << "Token" << ToString(token) << std::endl;
    }

    std::queue<TNode> pendingToString;
    pendingToString.push(result);

    while (!pendingToString.empty()) {
        auto toProcess = pendingToString.front();
        pendingToString.pop();
        cout << ToString(toProcess) << endl;
        if (!toProcess.children.empty()) {
            auto childrenArr = (toProcess).children;
            for (const auto& child : childrenArr) {
                pendingToString.push(child);
            }
        }
    }

    PKB pkbinstance = PKB();
    DesignExtractor designExtractor;

    try {
        designExtractor.extractAbstraction(result, pkbinstance);
    }
    catch (std::invalid_argument& theException) {
        std::cerr << theException.what() << endl;
        ::exit(1);
    }

    vector<Cfg> controlFlowGraphs;
    for (const auto& procedure: result.children) {
        Cfg controlFlowGraph = Cfg(procedure);
        controlFlowGraph.buildCfg(procedure, -1);
        controlFlowGraphs.push_back(controlFlowGraph);
        pkbinstance.addControlFlowGraph(procedure.stringId, controlFlowGraph.basicBlock,
                                        controlFlowGraph.blockToStatement,
                                        controlFlowGraph.statementNumberToBlock,
                                        controlFlowGraph.blockGraph,
                                        controlFlowGraph.blockPointingBackward);
        std::cout << controlFlowGraph.toString() << std::endl;

        NextExtractor nextExtractor;
        nextExtractor.extractAbstraction(controlFlowGraph.basicBlock, controlFlowGraph.blockToStatement,
                                         controlFlowGraph.statementNumberToBlock, controlFlowGraph.blockGraph,
                                         controlFlowGraph.blockPointingBackward, pkbinstance, procedure.stringId);
    }
}
