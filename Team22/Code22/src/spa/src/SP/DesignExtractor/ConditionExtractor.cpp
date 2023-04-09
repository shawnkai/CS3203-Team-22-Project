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
			pkbinstance.addDesignAbstraction("USES", make_tuple(procedureStr, procedureName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple(procedureStr, nameOfVariable, procedureName));
			cout << std::to_string(lineNumOfVariable) + " uses procedure " + procedureName << endl;
			cout << nameOfVariable + " uses procedure " + procedureName << endl;

			Result result1 = pkbinstance.getDesignAbstraction("INVERSECALLS", make_pair("_", procedureName));
			std::vector<std::string> vector1 = result1.getQueryResult();
			for (int i = 0; i < vector1.size(); i++) {
				if (vector1[i] != "none") {
					pkbinstance.addDesignAbstraction("USES", make_tuple(procedureStr, vector1[i], std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("USES", make_tuple(procedureStr, nameOfVariable, vector1[i]));
					cout << std::to_string(lineNumOfVariable) + " uses procedure " + vector1[i] << endl;
					cout << nameOfVariable + " uses procedure " + vector1[i] << endl;
				}
				Result result3 = pkbinstance.getDesignEntity("CALL", vector1[i]);
				std::vector<std::string> vector3 = result3.getQueryResult();
				for (int j = 0; j < vector3.size(); j++) {
					if (vector3[j] != "none") {
						pkbinstance.addDesignAbstraction("USES", make_tuple(procedurecallStr, vector3[j], std::to_string(lineNumOfVariable)));
						pkbinstance.addDesignAbstraction("USES", make_tuple(procedurecallStr, nameOfVariable, vector3[j]));
						pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, vector3[j]));
						cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector3[j] << endl;

						if (mapOfUsedVarforCalls.count(vector3[j]) > 0) {
							vector<string> usedVars = mapOfUsedVarforCalls.at(vector3[j]);
							usedVars.push_back(nameOfVariable);
							mapOfUsedVarforCalls[vector3[j]] = usedVars;
						}
						else {
							vector<string> usedVars;
							usedVars.push_back(nameOfVariable);
							mapOfUsedVarforCalls[vector3[j]] = usedVars;
						}

						cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector3[j] << endl;
					}
				}
			}

			Result result2 = pkbinstance.getDesignEntity("CALL", procedureName);
			std::vector<std::string> vector2 = result2.getQueryResult();
			for (int i = 0; i < vector2.size(); i++) {
				if (vector2[i] != "none") {
					pkbinstance.addDesignAbstraction("USES", make_tuple(procedurecallStr, vector2[i], std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("USES", make_tuple(procedurecallStr, nameOfVariable, vector2[i]));
					pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, vector2[i]));
					cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector2[i] << endl;

					if (mapOfUsedVarforCalls.count(vector2[i]) > 0) {
						vector<string> usedVars = mapOfUsedVarforCalls.at(vector2[i]);
						usedVars.push_back(nameOfVariable);
						mapOfUsedVarforCalls[vector2[i]] = usedVars;
					}
					else {
						vector<string> usedVars;
						usedVars.push_back(nameOfVariable);
						mapOfUsedVarforCalls[vector2[i]] = usedVars;
					}

					cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector2[i] << endl;
				}
			}

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
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << whileContainers[i] << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple(whileStr, nameOfVariable, whileContainers[i]));
					pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, whileContainers[i]));
				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << ifContainers[i] << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple(ifStr, nameOfVariable, ifContainers[i]));
					pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, ifContainers[i]));
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