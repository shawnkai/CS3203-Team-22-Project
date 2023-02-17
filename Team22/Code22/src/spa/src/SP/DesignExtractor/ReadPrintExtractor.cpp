#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "ReadPrintExtractor.h"
/*#include "PKB.h"
#include "TNode.h"*/
//#include "Token.h"


void ReadPrintExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		std::string tokenType1 = ToString(currentNode.nodeType);
		std::vector<TNode> childNodes = currentNode.children;
		TNode childNode = childNodes[0];
		std::string variableName = childNode.stringId;
		int lineNumOfVariable = childNode.stmtNumber;
		cout << variableName << endl;
		
		if (tokenType1 == "READ") {
			//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("READ", variableName, std::to_string(lineNumOfVariable)));
			//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			//pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << std::to_string(whileContainers[i]) << endl;

					//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[i])));
				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << std::to_string(ifContainers[i]) << endl;
					//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("IF", nameOfVariable, std::to_string(ifContainers[i])));
				}
			}
		}
		else if (tokenType1 == "PRINT") {
			//pkbinstance.addDesignAbstraction("USES", make_tuple("PRINT", variableName, std::to_string(lineNumOfVariable)));
			//pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			//pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int i = 0; i < whileContainers.size(); i++) {
					cout << std::to_string(whileContainers[i]) << endl;
					//pkbinstance.addDesignAbstraction("USES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[i])));
				}
			}
			if (ifContainers.size() != 0) {
				for (int i = 0; i < ifContainers.size(); i++) {
					cout << std::to_string(ifContainers[i]) << endl;
					//pkbinstance.addDesignAbstraction("USES", make_tuple("IF", nameOfVariable, std::to_string(ifContainers[i])));
				}
			}

		}
		else {
		}
			
	}
};