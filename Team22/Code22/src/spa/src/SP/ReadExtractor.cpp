#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "ReadExtractor.h"
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

void ReadExtractor::extractAbstraction(TNode root) {

	if (root.nodeType == UNKNOWN) {
		//if (root.nodeType == "NULL") {
		auto result = std::make_tuple("NULL");
		//return result;
	}
	else {
		queue<TNode> queue1;
		queue1.push(root);
		std::string procedureName;
		std::string result1;//deletelater
		int procedureLineNo;
		while (queue1.size() != 0) {
			int size1 = queue1.size();
			TNode currentNode = queue1.front();
			TokenType tokenType;
			tokenType = currentNode.nodeType;
			std::string tokenType1 = ToString(tokenType);
			//std::string tokenType1 = currentNode.nodeType;
			if (tokenType1 == "PROCEDURE") {
				procedureName = currentNode.stringId;
				procedureLineNo = currentNode.stmtNumber;
				result1 = procedureName + std::to_string(procedureLineNo);//deletelater
				int noOfChildren = (currentNode.children).size();
				for (int j = 0; j < noOfChildren; j++) {
					std::vector<TNode> childNodes = currentNode.children;
					queue1.push(childNodes[j]);
				}
			}
			else {
				if (tokenType1 == "READ") {
					std::vector<TNode> childNodes = currentNode.children;
					TNode childNode = childNodes[0];
					std::string variableInRead = childNode.stringId;
					int lineNumOfVariable = childNode.stmtNumber;
					result1 = result1 + variableInRead + std::to_string(lineNumOfVariable);//deletelater
					auto tuple1 = std::make_tuple(result1);
					cout << result1;
					PKB pkbinstance = PKB();
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableInRead, procedureName));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("READ", variableInRead, std::to_string(lineNumOfVariable)));
                    pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", variableInRead, std::to_string(lineNumOfVariable)));

					//return result1;

				}
				else if (tokenType1 == "STATEMENT_LIST") {
					int noOfChildren = (currentNode.children).size();
					for (int j = 0; j < noOfChildren; j++) {
						std::vector<TNode> childNodes = currentNode.children;
						queue1.push(childNodes[j]);
					}
				}
				else {}

			}
			queue1.pop();


			//}
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