#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

#include "AbstractionExtractor.h"

/**
 * Extracts the abstractions and entities from the Abstract Syntax Tree and 
 * adds the abstractions and entities to the Program Knowledge Base.
 * 
 * @param root The root node of the Abstract Syntax Tree, of type TNode.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void AbstractionExtractor::extractAbstraction(TNode root, PKB pkbinstance, std::string procedureName) {
	std::vector<std::tuple<int, int>> followsVector;
	std::vector<std::tuple<int, int>> parentVector;


	if (root.nodeType != TokenType::PROCEDURE) {
		cout << "something went wrong" << endl;
	}
	else {
		std::string procedureName;
		procedureName = root.stringId;
		pkbinstance.addDesignEntity("PROCEDURE", make_tuple(procedureName, std::to_string(root.stmtNumber)));
		int noOfChildren = (root.children).size();
		if (noOfChildren == 0) {

		}
		else {
			for (int j = 0; j < noOfChildren; j++) {
				std::vector<TNode> childNodes = root.children;
				TNode currentNode = childNodes[j];
				if (currentNode.nodeType == STATEMENT_LIST) {
					StmtlstExtractor stmtlstExtractor;
					std::vector<int> ifContainer = std::vector<int>(0);
					std::vector<int> whileContainer = std::vector<int>(0);
					int currentParent = 0;
					stmtlstExtractor.extractAbstraction(currentNode, ifContainer, whileContainer, pkbinstance, currentParent, procedureName);
				}

			}
		}

	}
};
