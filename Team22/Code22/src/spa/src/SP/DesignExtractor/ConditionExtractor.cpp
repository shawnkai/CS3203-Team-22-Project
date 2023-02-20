#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "ConditionExtractor.h"

/**
 * Extracts the abstractions and entities from a condition of an if or while statement and
 * adds the abstractions and entities to the Program Knowledge Base. If the current if 
 * or while statement is nested in other if or while statements, then the related abstractions
 * would also be added to the Program Knowledge Base.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that the current statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that the current statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void ConditionExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {
	std::string nodeType1 = ToString(currentNode.nodeType);
	queue<TNode> queue1;
	queue1.push(currentNode);
	while (queue1.size() != 0) {
		TNode currentNode1 = queue1.front();
		TokenType tokenType1 = currentNode1.nodeType;
		if (tokenType1 == TokenType::NAME_IDENTIFIER) {
			std::string nameOfVariable = currentNode1.stringId;
			int lineNumOfVariable = currentNode1.stmtNumber;
			cout << currentNode1.stringId << endl;
			pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << std::to_string(whileContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[i])));
					pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, std::to_string(whileContainers[i])));
				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << std::to_string(ifContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple("IF", nameOfVariable, std::to_string(ifContainers[i])));
					pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, std::to_string(ifContainers[i])));
				}
			}

		}
		else if (tokenType1 == TokenType::OPERATOR) {
			std::vector<TNode> childNodes = currentNode1.children;
			for (int i = 0; i < childNodes.size(); i++) {
				queue1.push(childNodes[i]);
			}
		}
		else if (tokenType1 == TokenType::INTEGER) {
			std::string stringOfConstant = currentNode1.stringId;
			pkbinstance.addDesignEntity("CONSTANT", make_tuple(stringOfConstant, std::to_string(currentNode1.stmtNumber)));

		}
		else {}
		queue1.pop();


	}
};