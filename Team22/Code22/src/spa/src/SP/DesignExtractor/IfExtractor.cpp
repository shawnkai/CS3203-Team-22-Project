#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "IfExtractor.h"



void IfExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType == UNKNOWN) {
		cout << "something went wrong" << endl;
	}
	else {
		int ifLineNo = currentNode.stmtNumber;
        pkbinstance.addDesignEntity("IF", make_tuple("IF", std::to_string(ifLineNo)));
        pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(ifLineNo)));
		ifContainers.push_back(ifLineNo);
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		ConditionExtractor conditionExtractor;
		conditionExtractor.extractAbstraction(conditionNode, ifContainers, whileContainers, pkbinstance);
		TNode ifstmtlstNode = childNodes[1];
		StmtlstExtractor stmtlstExtractor;
		stmtlstExtractor.extractAbstraction(ifstmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo);
		TNode elsestmtlstNode = childNodes[2];
		StmtlstExtractor stmtlstExtractor2;
		stmtlstExtractor2.extractAbstraction(elsestmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo);
	}

};