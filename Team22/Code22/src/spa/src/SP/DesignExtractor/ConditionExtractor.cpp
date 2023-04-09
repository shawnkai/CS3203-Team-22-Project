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
 * @param procedureName The name of the procedure.
 * @param prevNode The parent node of the current node.
 */
void ConditionExtractor::extractConditionAbstraction(TNode currentNode, std::vector<string> ifContainers, std::vector<string> whileContainers, PKB pkbinstance, std::string procedureName, TNode prevNode) {
	std::string nodeType1 = ToString(currentNode.nodeType);
	queue<TNode> queue1;
	queue1.push(currentNode);
	std::string statementStr = "STATEMENT";
	std::string procedureStr = "PROCEDURE";
	std::string procedurecallStr = "PROCEDURECALL";
	std::string ifStr = "IF";
	std::string whileStr = "WHILE";
	while (queue1.size() != 0) {
		TNode currentNode1 = queue1.front();
		TokenType tokenType1 = currentNode1.nodeType;
		if (tokenType1 == TokenType::NAME_IDENTIFIER) {
			std::string nameOfVariable = currentNode1.stringId;
			int lineNumOfVariable = currentNode1.stmtNumber;
			cout << currentNode1.stringId << endl;
			pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, std::to_string(lineNumOfVariable)));
            RelationshipExtractor relationshipExtractor;
            relationshipExtractor.extractModifiesorUsesAbstraction("USES", pkbinstance, procedureName, nameOfVariable, lineNumOfVariable);
            relationshipExtractor.extractContainerUsesOrModifiesAbstraction("USES", ifContainers, whileContainers, pkbinstance, nameOfVariable);
            pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));

			if (prevNode.nodeType == TokenType::IF) {
				pkbinstance.addPattern("IF", std::to_string(lineNumOfVariable), nameOfVariable);
				cout << std::to_string(lineNumOfVariable) + " pattern ifs " + nameOfVariable << endl;
			}
			else if (prevNode.nodeType == TokenType::WHILE) {
				pkbinstance.addPattern("WHILE", std::to_string(lineNumOfVariable), nameOfVariable);
				cout << std::to_string(lineNumOfVariable) + " pattern w " + nameOfVariable << endl;
			}
			else {

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