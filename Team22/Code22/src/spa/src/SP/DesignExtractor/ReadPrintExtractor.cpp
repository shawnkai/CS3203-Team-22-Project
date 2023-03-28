#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "ReadPrintExtractor.h"

/**
 * Extracts the abstractions and entities from a read statement or a print statement, and adds
 * the abstractions and entities to the Program Knowledge Base. If the current statement is 
 * nested in other if or while statements, then the related abstractions would also be added
 * to the Program Knowledge Base.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that the current statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that the current statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void ReadPrintExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, std::string procedureName) {

	if (currentNode.nodeType == TokenType::UNKNOWN) {
		cout << "something went wrong" << endl;
	}
	else {
		TokenType tokenType1 = currentNode.nodeType;
		std::vector<TNode> childNodes = currentNode.children;
		TNode childNode = childNodes[0];
		std::string variableName = childNode.stringId;
		int lineNumOfVariable = childNode.stmtNumber;
		cout << variableName << endl;

		if (tokenType1 == TokenType::READ) {
			pkbinstance.addDesignEntity("READ", make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity("STATEMENT", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("READ", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", procedureName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, procedureName));
			cout << std::to_string(lineNumOfVariable) + " modifies procedure " + procedureName << endl;
			cout << variableName + " modifies procedure " + procedureName << endl;

			Result result1 = pkbinstance.getDesignAbstraction("INVERSECALLS", make_pair("_", procedureName));
			std::vector<std::string> vector1 = result1.getQueryResult();	
			for (int i = 0; i < vector1.size(); i++) {
				if (vector1[i] != "none") {
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", vector1[i], std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, vector1[i]));
					cout << std::to_string(lineNumOfVariable) + " modifies procedure " + vector1[i] << endl;
					cout << variableName + " modifies procedure " + vector1[i] << endl;
				}
				Result result3 = pkbinstance.getDesignEntity("CALL", vector1[i]);
				std::vector<std::string> vector3 = result3.getQueryResult();		
				for (int j = 0; j < vector3.size(); j++) {
					if (vector3[j] != "none") {
						pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", vector3[j], std::to_string(lineNumOfVariable)));
						cout << std::to_string(lineNumOfVariable) + " modifies procedureCall " + vector3[j] << endl;
					}
				}
			}
			
			Result result2 = pkbinstance.getDesignEntity("CALL", procedureName);
			std::vector<std::string> vector2 = result2.getQueryResult();
			for (int i = 0; i < vector2.size(); i++) {
				if (vector2[i] != "none") {
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", vector2[i], std::to_string(lineNumOfVariable)));
					cout << std::to_string(lineNumOfVariable) + " modifies procedureCall " + vector2[i] << endl;
				}
			}
			
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << std::to_string(whileContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", variableName, std::to_string(whileContainers[i])));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(whileContainers[i])));
				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << std::to_string(ifContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("IF", variableName, std::to_string(ifContainers[i])));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(ifContainers[i])));

				}
			}
		}
		else if (tokenType1 == TokenType::PRINT) {
			pkbinstance.addDesignEntity("PRINT", make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity("STATEMENT", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple("PRINT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURE", procedureName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURE", variableName, procedureName));
			cout << std::to_string(lineNumOfVariable) + " uses procedure " + procedureName << endl;
			cout << variableName + " uses procedure " + procedureName << endl;

			Result result1 = pkbinstance.getDesignAbstraction("INVERSECALLS", make_pair("_", procedureName));
			std::vector<std::string> vector1 = result1.getQueryResult();
			for (int i = 0; i < vector1.size(); i++) {
				if (vector1[i] != "none") {
					pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURE", vector1[i], std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURE", variableName, vector1[i]));
					cout << std::to_string(lineNumOfVariable) + " uses procedure " + vector1[i] << endl;
					cout << variableName + " uses procedure " + vector1[i] << endl;
				}
				Result result3 = pkbinstance.getDesignEntity("CALL", vector1[i]);
				std::vector<std::string> vector3 = result3.getQueryResult();
				for (int j = 0; j < vector3.size(); j++) {
					if (vector3[j] != "none") {
						pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", vector3[j], std::to_string(lineNumOfVariable)));
						cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector3[j] << endl;
					}
				}
			}
			
			Result result2 = pkbinstance.getDesignEntity("CALL", procedureName);
			std::vector<std::string> vector2 = result2.getQueryResult();
			for (int i = 0; i < vector2.size(); i++) {
				if (vector2[i] != "none") {
					pkbinstance.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", vector2[i], std::to_string(lineNumOfVariable)));
					cout << std::to_string(lineNumOfVariable) + " uses procedureCall " + vector2[i] << endl;
				}
			}
			
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << std::to_string(whileContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple("WHILE", variableName, std::to_string(whileContainers[i])));
					pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", variableName, std::to_string(whileContainers[i])));

				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << std::to_string(ifContainers[i]) << endl;
					pkbinstance.addDesignAbstraction("USES", make_tuple("IF", variableName, std::to_string(ifContainers[i])));
					pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", variableName, std::to_string(ifContainers[i])));

				}
			}

		}
		else {
		}
			
	}
};