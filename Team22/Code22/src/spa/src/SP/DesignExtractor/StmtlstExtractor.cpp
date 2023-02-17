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



void StmtlstExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance, int currentParent) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		std::vector<TNode> childstmts = currentNode.children;
		for (int i = 0; i < childstmts.size() - 1; i++) {
			TNode currentStmt = childstmts[i];
			int nextNo = i + 1;
			TNode nextStmt = childstmts[nextNo];
			int currentLineNo = currentStmt.stmtNumber;
			std::string showFollows = "follows" + std::to_string(currentLineNo) + std::to_string(nextStmt.stmtNumber);
			cout << showFollows << endl;
			//pkbinstance.addDesignAbstraction("FOLLOWS", make_tuple("_", std::to_string(currentLineNo), std::to_string(nextStmt.stmtNumber)));
			for (int j = i + 1; j < childstmts.size(); j++) {
				TNode stmt2 = childstmts[j];
				//pkbinstance.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", std::to_string(currentLineNo), std::to_string(stmt2.stmtNumber)));
				std::string showFollowsStar = "followsstar" + std::to_string(currentLineNo) + std::to_string(stmt2.stmtNumber);
				cout << showFollowsStar << endl;
			}
		}
		for (int i = 0; i < childstmts.size(); i++) {
			TNode currentStmt = childstmts[i];
			std::string showParent = "parent" + std::to_string(currentParent) + std::to_string(currentStmt.stmtNumber);
			cout << showParent << endl;
			//pkbinstance.addDesignAbstraction("PARENT", make_tuple("_", std::to_string(currentParent), std::to_string(currentStmt.stmtNumber)));
			if (whileContainers.size() != 0) {
				for (int j = 0; j < whileContainers.size(); j++) {
					std::string showParentWhileStar = "followsstar" + std::to_string(whileContainers[j]) + std::to_string(currentStmt.stmtNumber);
					cout << showParentWhileStar << endl;
					//pkbinstance.addDesignAbstraction("PARENTSTAR", make_tuple("_", std::to_string(whileContainers[j]), std::to_string(currentStmt.stmtNumber)));
				}
			}
			if (ifContainers.size() != 0) {
				for (int j = 0; j < ifContainers.size(); j++) {
					std::string showParentIfStar = "followsstar" + std::to_string(ifContainers[i]) + std::to_string(currentStmt.stmtNumber);
					cout << showParentIfStar << endl;
					//pkbinstance.addDesignAbstraction("PARENTSTAR", make_tuple("_", std::to_string(ifContainers[j]), std::to_string(currentStmt.stmtNumber)));
				}
			}
		}

		for (auto& childstmt : childstmts) {
			std::string tokenType1 = ToString(childstmt.nodeType);
			if ((tokenType1 == "READ") || (tokenType1 == "PRINT")) {
				ReadPrintExtractor readPrintExtractor;
				readPrintExtractor.extractAbstraction(currentNode, ifContainers, whileContainers, pkbinstance);
			}
			else if (tokenType1 == "WHILE") {
				WhileExtractor whileExtractor1;
				whileExtractor1.extractAbstraction(childstmt, ifContainers, whileContainers, pkbinstance);
				//cout << "2";
			}
			else if (tokenType1 == "IF") {
				IfExtractor ifExtractor1;
				ifExtractor1.extractAbstraction(childstmt, ifContainers, whileContainers, pkbinstance);

			}
			else if (tokenType1 == "ASSIGN") {
				AssignExtractor assignExtractor1;
				assignExtractor1.extractAbstraction(childstmt, ifContainers, whileContainers, pkbinstance);
			}
		}

	}

};