#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

/*#include "PKB.h"
#include "ReadExtractor.h"
#include "TNode.h"*/
#include "AbstractionExtractor.h"

//class AbstractionExtractor {
	//ReadExtractor readExtractor;
//public:
//AbstractionExtractor() {

//};



void AbstractionExtractor::extractAbstraction(TNode root) {
	std::vector<std::tuple<int, int>> followsVector;
	std::vector<std::tuple<int, int>> parentVector;


	if (root.nodeType != PROCEDURE) {
		cout << "something went wrong" << endl;
	}
	else {
		std::string procedureName;
		procedureName = root.stringId;
		int noOfChildren = (root.children).size();
		for (int j = 0; j < noOfChildren; j++) {
			std::vector<TNode> childNodes = root.children;
			TNode currentNode = childNodes[j];
			if (currentNode.nodeType == STATEMENT_LIST) {
				StmtlstExtractor stmtlstExtractor;
				std::vector<int> ifContainer = std::vector<int>(0);
				std::vector<int> whileContainer = std::vector<int>(0);
				PKB pkbinstance = PKB();
				int currentParent = 0;
				stmtlstExtractor.extractAbstraction(currentNode, ifContainer, whileContainer, pkbinstance, currentParent);
			}
			
		}

	}
};
