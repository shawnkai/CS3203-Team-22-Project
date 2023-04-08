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
void IfExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName) {

    if (currentNode.nodeType != TokenType::IF) {
        cout << "something went wrong" << endl;
    } else {
        int ifLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(ifLineNo)));
        pkbinstance.addDesignEntity("IF", make_tuple(currentNode.stringId, std::to_string(ifLineNo)));
        ifContainers.push_back(ifLineNo);
        std::vector<TNode> childNodes = currentNode.children;
        TNode conditionNode = childNodes[0];
        ConditionExtractor conditionExtractor;
        conditionExtractor.extractAbstraction(conditionNode, ifContainers, whileContainers, pkbinstance, procedureName, currentNode);
        TNode ifstmtlstNode = childNodes[1];
        StmtlstExtractor stmtlstExtractor;
        stmtlstExtractor.extractAbstraction(ifstmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo, procedureName);
        TNode elsestmtlstNode = childNodes[2];
        StmtlstExtractor stmtlstExtractor2;
        stmtlstExtractor2.extractAbstraction(elsestmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo, procedureName);
    }
};