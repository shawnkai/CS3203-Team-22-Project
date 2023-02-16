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



//class ReadExtractor {
//public:
	//ReadExtractor() {

	//};

std::string ReadPrintExtractor::extractAbstraction(TNode currentNode) {

	if (currentNode.nodeType == UNKNOWN) {
		//auto result = std::make_tuple("NULL");
		return "";
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
		PKB pkbinstance = PKB();
		
		if (tokenType1 == "READ") {
			//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, procedureName));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("READ", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			return variableName;
		}
		else if (tokenType1 == "PRINT") {
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PRINT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			return variableName;

		}
		else {
			return "";
		}
			
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