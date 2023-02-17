#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "WhileExtractor.h"
/*#include "PKB.h"
#include "TNode.h"*/
//#include "Token.h"



void WhileExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
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
