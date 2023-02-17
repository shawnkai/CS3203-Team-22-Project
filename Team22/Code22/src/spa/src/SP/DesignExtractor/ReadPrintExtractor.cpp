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
		std::string result1;
		result1 = result1 + variableName + std::to_string(lineNumOfVariable);//deletelater
		auto tuple1 = std::make_tuple(result1);
		cout << result1;
		
		if (tokenType1 == "READ") {
			//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, procedureName));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("READ", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			for (int j = 0; j < whileContainers.size(); j++) {
				cout << std::to_string(whileContainers[j]) << endl;
				//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[j])));
			}
			for (int i = 0; i < ifContainers.size(); i++) {
				cout << std::to_string(ifContainers[i]) << endl;
				//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("IF", nameOfVariable, std::to_string(ifContainers[i])));
			}
		}
		else if (tokenType1 == "PRINT") {
			//pkbinstance.addDesignAbstraction("USES", make_tuple("PRINT", variableName, std::to_string(lineNumOfVariable)));
			//pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			if (whileContainers.size() != 0) {
				for (int j = 0; j < whileContainers.size(); j++) {
					cout << std::to_string(whileContainers[j]) << endl;
					//pkbinstance.addDesignAbstraction("USES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[j])));
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