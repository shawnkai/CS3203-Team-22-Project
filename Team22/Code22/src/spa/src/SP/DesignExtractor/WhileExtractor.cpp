#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "WhileExtractor.h"
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



void WhileExtractor::extractAbstraction(TNode currentNode) {

	if (currentNode.nodeType == UNKNOWN) {
		//return "";
	}
	else {
		int whileLineNo = currentNode.stmtNumber;
		std::vector<TNode> childNodes = currentNode.children;
		TNode conditionNode = childNodes[0];
		TNode stmtlstNode = childNodes[1];//"stmtlst" node
		StmtlstExtractor stmtlstExtractor;
		stmtlstExtractor.extractAbstraction(stmtlstNode);
		/*std::vector<TNode> childstmts = stmtlstNode.children;
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
					//change to USES later
				}
				else {}
				
			}
			else if (tokenType1 == "WHILE") {
				WhileExtractor whileExtractor1;
				whileExtractor1.extractAbstraction(childstmt);
				cout << "2";

			}
			else {
			
			}
		}*/
	}
		
};

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

	WhileExtractor readExtractor;
	readExtractor.extractAbstraction(root);
};*/