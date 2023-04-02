#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "AssignExtractor.h"

/**
 * Extracts the abstractions and entities from an assignment statement and
 * adds the abstractions and entities to the Program Knowledge Base. If the assignment 
 * statement is nested in if or while statements, then the related abstractions
 * would also be added to the Program Knowledge Base.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that this assignment statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that this assignment statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void AssignExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName) {
	TokenType nodeType1 = currentNode.nodeType;
	std::string assignmentStr = "ASSIGNMENT";
	std::string statementStr = "STATEMENT";
	std::string procedureStr = "PROCEDURE";
	std::string procedurecallStr = "PROCEDURECALL";
	std::string ifStr = "IF";
	std::string whileStr = "WHILE";

	if (nodeType1 != TokenType::ASSIGN) {
		cout << "something went wrong" << endl;
	}
	else {
		pkbinstance.addDesignEntity("ASSIGNMENT", make_tuple(currentNode.stringId, std::to_string(currentNode.stmtNumber)));
		PatternPrefixStringExtractor prefixExtractor;
		prefixExtractor.extractPrefixString(currentNode, pkbinstance);
		queue<TNode> queue1;
		int firstTime = 0;
		queue1.push(currentNode);
		while (queue1.size() != 0) {
			TNode currentNode1 = queue1.front();
			TokenType tokenType1 = currentNode1.nodeType;
			if (tokenType1 == TokenType::NAME_IDENTIFIER) {
				std::string nameOfVariable = currentNode1.stringId;
				int lineNumOfVariable = currentNode1.stmtNumber;
                pkbinstance.addDesignEntity("ASSIGNMENT", make_tuple("ASSIGNMENT", std::to_string(lineNumOfVariable)));
                pkbinstance.addDesignEntity("STATEMENT", make_tuple("STATEMENT", std::to_string(lineNumOfVariable)));
				cout << currentNode1.stringId << endl;
				if (firstTime == 0) {
					firstTime = 1;
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(assignmentStr, nameOfVariable, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, nameOfVariable, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(procedureStr, procedureName, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(procedureStr, nameOfVariable, procedureName));
					cout << std::to_string(lineNumOfVariable) + " modifies procedure " + procedureName << endl;
					cout << nameOfVariable + " modifies procedure " + procedureName << endl;

					Result result1 = pkbinstance.getDesignAbstraction("INVERSECALLS", make_pair("_", procedureName));
					std::vector<std::string> vector1 = result1.getQueryResult();
					for (int i = 0; i < vector1.size(); i++) {
						if (vector1[i] != "none") {
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(procedureStr, vector1[i], std::to_string(lineNumOfVariable)));
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(procedureStr, nameOfVariable, vector1[i]));
							cout << std::to_string(lineNumOfVariable) + " modifies procedure " + vector1[i] << endl;
							cout << nameOfVariable + " modifies procedure " + vector1[i] << endl;
						}
						Result result3 = pkbinstance.getDesignEntity("CALL", vector1[i]);
						std::vector<std::string> vector3 = result3.getQueryResult();
						for (int j = 0; j < vector3.size(); j++) {
							if (vector3[j] != "none") {
								pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", vector3[j], std::to_string(lineNumOfVariable)));
								pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", nameOfVariable, vector3[j]));
								pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", nameOfVariable, vector3[j]));

								if (mapOfModifiedVarforCalls.count(vector3[j]) > 0) {
									vector<string> modifiedVars = mapOfModifiedVarforCalls.at(vector3[j]);
									modifiedVars.push_back(nameOfVariable);
									mapOfModifiedVarforCalls[vector3[j]] = modifiedVars;
								}
								else {
									vector<string> modifiedVars;
									modifiedVars.push_back(nameOfVariable);
									mapOfModifiedVarforCalls[vector3[j]] = modifiedVars;
								}

								cout << std::to_string(lineNumOfVariable) + " modifies procedureCall " + vector3[j] << endl;
							}
						}
					}

					Result result2 = pkbinstance.getDesignEntity("CALL", procedureName);
					std::vector<std::string> vector2 = result2.getQueryResult();
					for (int i = 0; i < vector2.size(); i++) {
						if (vector2[i] != "none") {
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", vector2[i], std::to_string(lineNumOfVariable)));
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", nameOfVariable, vector2[i]));
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", nameOfVariable, vector2[i]));

							if (mapOfModifiedVarforCalls.count(vector2[i]) > 0) {
								vector<string> modifiedVars = mapOfModifiedVarforCalls.at(vector2[i]);
								modifiedVars.push_back(nameOfVariable);
								mapOfModifiedVarforCalls[vector2[i]] = modifiedVars;
							}
							else {
								vector<string> modifiedVars;
								modifiedVars.push_back(nameOfVariable);
								mapOfModifiedVarforCalls[vector2[i]] = modifiedVars;
							}

							cout << std::to_string(lineNumOfVariable) + " modifies procedureCall " + vector2[i] << endl;

						}
					}

					pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
					if (whileContainers.size() != 0) {
						for (int i = 0; i < whileContainers.size(); i++) {
							cout << std::to_string(whileContainers[i]) << endl;
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(whileStr, nameOfVariable, std::to_string(whileContainers[i])));
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, nameOfVariable, std::to_string(whileContainers[i])));
						}
					}
					if (ifContainers.size() != 0) {
						for (int i = 0; i < ifContainers.size(); i++) {
							cout << std::to_string(ifContainers[i]) << endl;
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(ifStr, nameOfVariable, std::to_string(ifContainers[i])));
							pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, nameOfVariable, std::to_string(ifContainers[i])));
						}
					}

				}
				else {
					pkbinstance.addDesignAbstraction("USES", make_tuple(assignmentStr, nameOfVariable, std::to_string(lineNumOfVariable)));
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
								pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", vector3[j], std::to_string(lineNumOfVariable)));
								pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", nameOfVariable, vector3[j]));
								pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, vector3[j]));

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
							pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", vector2[i], std::to_string(lineNumOfVariable)));
							pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", nameOfVariable, vector2[i]));
							pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, vector2[i]));

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

					pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
					if (whileContainers.size() != 0) {
						for (int i = 0; i < whileContainers.size(); i++) {
							cout << std::to_string(whileContainers[i]) << endl;
							pkbinstance.addDesignAbstraction("USES", make_tuple(whileStr, nameOfVariable, std::to_string(whileContainers[i])));
							pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, std::to_string(whileContainers[i])));
						}
					}
					if (ifContainers.size() != 0) {
						for (int i = 0; i < ifContainers.size(); i++) {
							cout << std::to_string(ifContainers[i]) << endl;
							pkbinstance.addDesignAbstraction("USES", make_tuple(ifStr, nameOfVariable, std::to_string(ifContainers[i])));
							pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, nameOfVariable, std::to_string(ifContainers[i])));

						}
					}
				}

			}
			else if (tokenType1 == TokenType::OPERATOR) {
				std::vector<TNode> childNodes = currentNode1.children;
				for (int i = 0; i < childNodes.size(); i++) {
					queue1.push(childNodes[i]);
				}
			}
			else if (tokenType1 == TokenType::ASSIGN) {
				std::vector<TNode> childNodes = currentNode1.children;
				for (int i = 0; i < childNodes.size(); i++) {
					queue1.push(childNodes[i]);
				}
			}
			else if (tokenType1 == TokenType::INTEGER) {
				std::string stringOfConstant = currentNode1.stringId;
                pkbinstance.addDesignAbstraction("USES", make_tuple(assignmentStr, stringOfConstant, std::to_string(currentNode1.stmtNumber)));
                pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, stringOfConstant, std::to_string(currentNode1.stmtNumber)));
                pkbinstance.addDesignEntity("CONSTANT", make_tuple(stringOfConstant, std::to_string(currentNode1.stmtNumber)));

			}
			else {}
			queue1.pop();
		
		}

	}
};