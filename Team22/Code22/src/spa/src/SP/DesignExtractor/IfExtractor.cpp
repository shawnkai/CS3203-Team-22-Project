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



void IfExtractor::extractAbstraction(TNode currentNode) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		TNode ifstmtlstNode = childNodes[1];//"stmtlst" node
		StmtlstExtractor stmtlstExtractor;
		stmtlstExtractor.extractAbstraction(ifstmtlstNode);
		TNode elsestmtlstNode = childNodes[1];
		StmtlstExtractor stmtlstExtractor2;
		stmtlstExtractor2.extractAbstraction(elsestmtlstNode);
	}

};