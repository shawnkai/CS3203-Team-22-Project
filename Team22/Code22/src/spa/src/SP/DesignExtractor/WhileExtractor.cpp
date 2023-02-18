#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "WhileExtractor.h"



void WhileExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType == UNKNOWN) {
		cout << "something went wrong" << endl;
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("WHILE", make_tuple("WHILE", std::to_string(whileLineNo)));
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(whileLineNo)));
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
