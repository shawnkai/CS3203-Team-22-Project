#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "AssignExtractor.h"
/*#include "PKB.h"
#include "TNode.h"*/
//#include "Token.h"

//change TNode to TNode1, Tokentype to string
/*class TNode1 {
public:
	std::string nodeType;
	std::string stringId;
	int stmtNumber;
	std::vector<TNode1> children;

	explicit TNode1(const std::string& type = "", const std::string& stringId = "",
		int stmtNumber = 0,
		const std::vector<TNode1>& children = std::vector<TNode1>(0)) :
		nodeType(type), stringId(stringId), stmtNumber(stmtNumber), children(children) {};
};*/


std::vector<std::string> AssignExtractor::extractAbstraction(TNode currentNode) {
	std::vector<std::string> variableVector;
	std::string nodeType1 = ToString(currentNode.nodeType);

	if (nodeType1 != "ASSIGN") {
		return variableVector;
	}
	else {
		queue<TNode> queue1;
		queue1.push(currentNode);
		while (queue1.size() != 0) {
			TNode currentNode1 = queue1.front();
			std::string tokenType1 = ToString(currentNode1.nodeType);
			if (tokenType1 == "NAME_IDENTIFIER") {
				std::string nameOfVariable = currentNode1.stringId;
				variableVector.push_back(nameOfVariable);
				cout << currentNode1.stringId << endl;

			}
			else if (tokenType1 == "OPERATOR") {
				std::vector<TNode> childNodes = currentNode1.children;
				for (auto& childNode1 : childNodes) {
					queue1.push(childNode1);
				}
			}
			else if (tokenType1 == "ASSIGN") {
				std::vector<TNode> childNodes = currentNode1.children;
				for (auto& childNode1 : childNodes) {
					queue1.push(childNode1);
				}
			}
			else {}
			queue1.pop();
		
		}
		return variableVector;

	}
};
//};

/*int main() {
	TNode1 var;
	var.nodeType = "NAME_IDENTIFIER";
	var.stringId = "x";
	var.stmtNumber = 2;
	var.children = std::vector<TNode1>(0);

	TNode1 read;
	read.nodeType = "READ";
	read.stringId = "read";
	read.stmtNumber = 2;
	read.children = std::vector<TNode1>{ var };

	TNode1 stmtlist;
	stmtlist.nodeType = "STATEMENT_LIST";
	stmtlist.stringId = "stmtlist";
	stmtlist.stmtNumber = 1;
	stmtlist.children = std::vector<TNode1>{ read };

	TNode1 root;
	root.nodeType = "PROCEDURE";
	root.stringId = "main";
	root.stmtNumber = 0;
	root.children = std::vector<TNode1>{ stmtlist };

	ReadExtractor readExtractor;
	readExtractor.extractAbstraction(root);
};*/