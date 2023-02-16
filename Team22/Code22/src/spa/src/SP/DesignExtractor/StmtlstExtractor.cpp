#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "StmtlstExtractor.h"
/*#include "PKB.h"
#include "TNode.h"*/
//#include "Token.h"



void StmtlstExtractor::extractAbstraction(TNode currentNode) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		std::vector<TNode> childstmts = currentNode.children;
		for (auto& childstmt : childstmts) {
			std::string tokenType1 = ToString(childstmt.nodeType);
			if ((tokenType1 == "READ") || (tokenType1 == "PRINT")) {
				cout << "1";
				ReadPrintExtractor readPrintExtractor;
				std::string variableName = readPrintExtractor.extractAbstraction(currentNode);
				if ((tokenType1 == "READ") && (variableName != "")) {
					PKB pkbinstance = PKB();
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", variableName, std::to_string(whileLineNo)));

				}
				else if ((tokenType1 == "PRINT") && (variableName != "")) {
					PKB pkbinstance = PKB();
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", variableName, std::to_string(whileLineNo)));
					change to USES later
				}
				else {}

			}
			else if (tokenType1 == "WHILE") {
				WhileExtractor whileExtractor1;
				whileExtractor1.extractAbstraction(childstmt);
				cout << "2";

			}
			else if (tokenType1 == "IF") {
				IfExtractor ifExtractor1;
				ifExtractor1.extractAbstraction(childstmt);

			}
			else {}
		}
	}

};