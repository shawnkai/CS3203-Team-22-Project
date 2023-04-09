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
        return std::make_shared<ProgramExtractor>(ProgramExtractor(currentNode, PKB pkbinstance));
    } else if (currentNode.nodeType == TokenType::PROCEDURE) {
        return std::make_shared<AbstractionExtractor>(AbstractionExtractor(currentNode, information, PKB pkbinstance));
    } else if (currentNode.nodeType == TokenType::STATEMENT_LIST) {
        return std::make_shared<StmtlstExtractor>(StmtlstExtractor(currentNode, information, PKB pkbinstance));
    } else if ((currentNode.nodeType == TokenType::READ) || (currentNode.nodeType == TokenType::PRINT)) {
        return std::make_shared<ReadPrintExtractor>(ReadPrintExtractor(currentNode, information, PKB pkbinstance));
    } else if (currentNode.nodeType == TokenType::WHILE) {
        return std::make_shared<WhileExtractor>(WhileExtractor(currentNode, information, PKB pkbinstance));
    } else if (currentNode.nodeType == TokenType::IF) {
        return std::make_shared<IfExtractor>(IfExtractor(currentNode, information, PKB pkbinstance));
    } else if (currentNode.nodeType == TokenType::ASSIGN) {
        return std::make_shared<AssignExtractor>(AssignExtractor(currentNode, information, PKB pkbinstance));
    } else {
        std::string containerTypeStr = "containerType";
        std::string underlineStr = "_";
        std::string isCondition = "isCondition";

        if (information.count(containerTypeStr) > 0) {
            vector<string> info1 = information.at(containerTypeStr);
            if (info1[0] != underlineStr) {
                if (info1[1] == isCondition) {
                    cout << "create ConditionExtractor" << endl;
                    return std::make_shared<ConditionExtractor>(ConditionExtractor(currentNode, information));
                }
            }
        }
    }
}
