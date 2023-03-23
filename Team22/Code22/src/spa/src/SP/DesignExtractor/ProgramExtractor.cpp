#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>

using namespace std;

#include "ProgramExtractor.h"

/**
 * Extracts the procedures from the Abstract Syntax Tree and call Abstraction
 * Extractor to extract the abstractions and entites from each procedure. 
 * The call and callStar relationships are added to the Program Knowledge Base.
 *
 * @param root The root node of the Abstract Syntax Tree, of type TNode.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void ProgramExtractor::extractAbstraction(TNode root, PKB pkbinstance) {
	std::map<std::string, std::vector<string>> mapOfCalls;
	std::vector<string> vectorOfProcedureNames;
	std::string underlineStr = "_";

	if (root.nodeType != TokenType::PROGRAM) {
		cout << "something went wrong" << endl;
	}
	else {
		int noOfProcedures;
		noOfProcedures = (root.children).size();
		cout << std::to_string(noOfProcedures) << endl;
		if (noOfProcedures == 0) {
			cout << "there are no procedures in this program" << endl;
		}
		else {
			std::vector<TNode> procedures = root.children;
			for (int i = 0; i < noOfProcedures; i++) {
				TNode procedureNode = procedures[i];
				std::string procedureName = procedureNode.stringId;
				vectorOfProcedureNames.push_back(procedureName);
				queue<TNode> queueOfNodes;
				queueOfNodes.push(procedureNode);
				while (queueOfNodes.size() > 0) {
					TNode current = queueOfNodes.front();
					if (current.nodeType == TokenType::CALL) {
						std::string procedureCalled = current.stringId;
						int callLineNo = current.stmtNumber;
						if (mapOfCalls.count(procedureName) > 0) {
							std::vector<string> vectorPrev = mapOfCalls.at(procedureName);
							vectorPrev.push_back(procedureCalled);
							mapOfCalls[procedureName] = vectorPrev;
						}
						else {
							std::vector<string> vectorNew;
							vectorNew.push_back(procedureCalled);
							mapOfCalls[procedureName] = vectorNew;
						}
						pkbinstance.addDesignAbstraction("CALLS", make_tuple(underlineStr, procedureName, procedureCalled));
						cout << procedureName + " calls " + procedureCalled << endl;
						pkbinstance.addDesignEntity("CALL", make_tuple(procedureCalled, std::to_string(callLineNo)));
						pkbinstance.addDesignEntity("STATEMENT", make_tuple(procedureCalled, std::to_string(callLineNo)));
					}
					else {

					}
					std::vector<TNode> children1 = current.children;
					if (children1.size() > 0) {
						for (int j = 0; j < children1.size(); j++) {
							queueOfNodes.push(children1[j]);
						}
					}
					queueOfNodes.pop();
				}

			}
			if (noOfProcedures == 1) {

			}
			else {
				for (int i = 0; i < noOfProcedures; i++) {
					std::string procedureName = vectorOfProcedureNames[i];
					queue<std::string> queueOfCalls;
					vector<std::string> vectorOfCallsSTAR;
					std::vector<string> vector1;
					if (mapOfCalls.count(procedureName) > 0) {
						vector1 = mapOfCalls.at(procedureName);
					}
					else {

					}
					
					set<std::string> setOfCalls;
					if (vector1.size() == 0) {

					}
					else {
						for (int j = 0; j < vector1.size(); j++) {
							queueOfCalls.push(vector1[j]);
							setOfCalls.insert(vector1[j]);
							vectorOfCallsSTAR.push_back(vector1[j]);
						}
						while (queueOfCalls.size() > 0) {
							std::string proceduareCalled = queueOfCalls.front();
							std::vector<string> vector2;
							if (mapOfCalls.count(proceduareCalled) > 0) {
								vector2 = mapOfCalls.at(proceduareCalled);
							}
							else {

							}
							for (int k = 0; k < vector2.size(); k++) {
								if (setOfCalls.count(vector2[k]) == 1) {

								}
								else {
									queueOfCalls.push(vector2[k]);
									setOfCalls.insert(vector2[k]);
									vectorOfCallsSTAR.push_back(vector2[k]);
								}
							}
							queueOfCalls.pop();
						}
					}
					for (int j = 0; j < vectorOfCallsSTAR.size(); j++) {
						pkbinstance.addDesignAbstraction("CALLSSTAR", make_tuple(underlineStr, procedureName, vectorOfCallsSTAR[j]));
						pkbinstance.addDesignAbstraction("INVERSECALLS", make_tuple(underlineStr, vectorOfCallsSTAR[j], procedureName));
						cout << procedureName + " callsStar " + vectorOfCallsSTAR[j] << endl;

					}

				}
			}
			for (int i = 0; i < noOfProcedures; i++) {
				std::vector<TNode> childNodes = root.children;
				TNode currentNode = childNodes[i];
				std::string procedureName = currentNode.stringId;
				AbstractionExtractor abstractionExtractor;
				abstractionExtractor.extractAbstraction(currentNode, pkbinstance, procedureName);
			}
			
		}

	}
};
