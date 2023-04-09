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
 * @param procedureName The name of the procedure.
 */
void AbstractionExtractor::extractAbstraction() {
	std::vector<std::tuple<int, int>> followsVector;
	std::vector<std::tuple<int, int>> parentVector;


	if (root.nodeType != TokenType::PROCEDURE) {
		cout << "something went wrong" << endl;
	}
	else {
		std::string procedureName;
		procedureName = root.stringId;
        pkbinstance.addDesignEntity(procedureStr, make_tuple(procedureName, std::to_string(root.stmtNumber)));
		int noOfChildren = (root.children).size();
		if (noOfChildren == 0) {

		}
		else {
			for (int j = 0; j < noOfChildren; j++) {
				std::vector<TNode> childNodes = root.children;
				TNode currentNode = childNodes[j];
				if (currentNode.nodeType == STATEMENT_LIST) {

                    ExtractorFactory factory1;
                    std::vector<string> ifContainer = std::vector<string>(0);
                    std::vector<string> whileContainer = std::vector<string>(0);
                    std::map<string, vector<string>> information = constructMap(ifContainer, whileContainer, procedureName, std::to_string(0));
                    auto stmtlstExtractor = factory1.createExtractor(currentNode, information, pkbinstance);
                    stmtlstExtractor->extractAbstraction();
				}

			}
		}

	}
};
