#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

#include "AbstractionExtractor.h"




void AbstractionExtractor::extractAbstraction(TNode root, PKB pkbinstance) {
	std::vector<std::tuple<int, int>> followsVector;
	std::vector<std::tuple<int, int>> parentVector;


	if (root.nodeType != TokenType::PROCEDURE) {
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
				int currentParent = 0;
				stmtlstExtractor.extractAbstraction(currentNode, ifContainer, whileContainer, pkbinstance, currentParent);
			}
			
		}

	}
};
