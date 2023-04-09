#include <iostream>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#include "../../PKB/PKB.h"
#include "ExtractorFactory.h"

std::shared_ptr<Extractor> ExtractorFactory::createExtractor(TNode currentNode, std::map<string, vector<string>> information, PKB pkbinstance) {
    if (currentNode.nodeType == TokenType::PROGRAM) {
        return std::make_shared<ProgramExtractor>(ProgramExtractor(currentNode, pkbinstance));
    } else if (currentNode.nodeType == TokenType::PROCEDURE) {
        return std::make_shared<AbstractionExtractor>(AbstractionExtractor(currentNode, information, pkbinstance));
    } else if (currentNode.nodeType == TokenType::STATEMENT_LIST) {
        return std::make_shared<StmtlstExtractor>(StmtlstExtractor(currentNode, information, pkbinstance));
    } else if ((currentNode.nodeType == TokenType::READ) || (currentNode.nodeType == TokenType::PRINT)) {
        return std::make_shared<ReadPrintExtractor>(ReadPrintExtractor(currentNode, information, pkbinstance));
    } else if (currentNode.nodeType == TokenType::WHILE) {
        return std::make_shared<WhileExtractor>(WhileExtractor(currentNode, information, pkbinstance));
    } else if (currentNode.nodeType == TokenType::IF) {
        return std::make_shared<IfExtractor>(IfExtractor(currentNode, information, pkbinstance));
    } else {
        return std::make_shared<AssignExtractor>(AssignExtractor(currentNode, information, pkbinstance));
    }
        
}
