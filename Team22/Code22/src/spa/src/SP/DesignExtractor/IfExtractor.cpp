#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


using namespace std;

#include "IfExtractor.h"

/**
 * Extracts the abstractions and entities from an if statement and adds the abstractions and
 * entities to the Program Knowledge Base. The ifContainers vector will be updated as well to
 * include the current if statement's line number.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that the current statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that the current statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void IfExtractor::extractAbstraction() {

    if (currentNode.nodeType != TokenType::IF) {
        cout << "something went wrong" << endl;
    } else {
        int ifLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(ifLineNo)));
        pkbinstance.addDesignEntity("IF", make_tuple(currentNode.stringId, std::to_string(ifLineNo)));
        ifContainers.push_back(std::to_string(ifLineNo));
        std::vector<TNode> childNodes = currentNode.children;
        TNode conditionNode = childNodes[0];
        ConditionExtractor conditionExtractor;
        conditionExtractor.extractConditionAbstraction(conditionNode, ifContainers, whileContainers, pkbinstance, procedureName, currentNode);
        TNode ifstmtlstNode = childNodes[1];
        ExtractorFactory factory1;
        std::map<string, vector<string>> information1 = constructMap(ifContainers, whileContainers, procedureName, std::to_string(ifLineNo));
        auto stmtlstExtractor1 = factory1.createExtractor(ifstmtlstNode, information1, pkbinstance);
        stmtlstExtractor1->extractAbstraction();
        
        TNode elsestmtlstNode = childNodes[2];
        ExtractorFactory factory2;
        std::map<string, vector<string>> information2 = constructMap(ifContainers, whileContainers, procedureName, std::to_string(ifLineNo));
        auto stmtlstExtractor2 = factory2.createExtractor(elsestmtlstNode, information2, pkbinstance);
        stmtlstExtractor2->extractAbstraction();
    }
};