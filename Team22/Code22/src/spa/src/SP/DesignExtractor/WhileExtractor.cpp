#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "WhileExtractor.h"

/**
 * Extracts the abstractions and entities from a while statement and adds the abstractions and
 * entities to the Program Knowledge Base. The whileContainers vector will be updated as well to
 * include the current while statement's line number.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that the current statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that the current statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void WhileExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType != TokenType::WHILE) {
		cout << "something went wrong" << endl;
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(whileLineNo)));
		pkbinstance.addDesignEntity("WHILE", make_tuple(currentNode.stringId, std::to_string(whileLineNo)));
		whileContainers.push_back(whileLineNo);
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		ConditionExtractor conditionExtractor;
		conditionExtractor.extractAbstraction(conditionNode, ifContainers, whileContainers, pkbinstance);
		TNode stmtlstNode = childNodes[1];
		StmtlstExtractor stmtlstExtractor;
		stmtlstExtractor.extractAbstraction(stmtlstNode, ifContainers, whileContainers, pkbinstance, whileLineNo);
	}
		
};
