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
 * @param procedureName The name of the procedure.
 */
void WhileExtractor::extractAbstraction() {

	if (currentNode.nodeType != TokenType::WHILE) {
		cout << "something went wrong" << endl;
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(whileLineNo)));
		pkbinstance.addDesignEntity("WHILE", make_tuple(currentNode.stringId, std::to_string(whileLineNo)));
		whileContainers.push_back(std::to_string(whileLineNo));
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		ConditionExtractor conditionExtractor;
		conditionExtractor.extractConditionAbstraction(conditionNode, ifContainers, whileContainers, pkbinstance, procedureName, currentNode);
		TNode stmtlstNode = childNodes[1];
        std::map<string, vector<string>> information2 = constructMap(ifContainers, whileContainers, procedureName, std::to_string(whileLineNo));
        ExtractorFactory factory1;
        auto stmtlstExtractor = factory1.createExtractor(stmtlstNode, information2, pkbinstance);
        stmtlstExtractor->extractAbstraction();
		//StmtlstExtractor stmtlstExtractor;
		//stmtlstExtractor.extractAbstraction(stmtlstNode, ifContainers, whileContainers, pkbinstance, whileLineNo, procedureName);
	}
		
};
