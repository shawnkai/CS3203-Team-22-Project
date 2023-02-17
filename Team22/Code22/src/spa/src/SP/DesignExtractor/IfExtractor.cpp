#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "IfExtractor.h"
/*#include "PKB.h"
#include "TNode.h"*/
//#include "Token.h"



void IfExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		int ifLineNo = currentNode.stmtNumber;
		ifContainers.push_back(ifLineNo);
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		TNode ifstmtlstNode = childNodes[1];
		StmtlstExtractor stmtlstExtractor;
		stmtlstExtractor.extractAbstraction(ifstmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo);
		TNode elsestmtlstNode = childNodes[2];
		StmtlstExtractor stmtlstExtractor2;
		stmtlstExtractor2.extractAbstraction(elsestmtlstNode, ifContainers, whileContainers, pkbinstance, ifLineNo);
	}

};