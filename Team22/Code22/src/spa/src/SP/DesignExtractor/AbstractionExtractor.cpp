#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

/*#include "PKB.h"
#include "ReadExtractor.h"
#include "TNode.h"*/
#include "AbstractionExtractor.h"

//class AbstractionExtractor {
	//ReadExtractor readExtractor;
//public:
//AbstractionExtractor() {

//};



void AbstractionExtractor::extractAbstraction(TNode root) {
	std::vector<std::tuple<int, int>> followsVector;
	std::vector<std::tuple<int, int>> parentVector;


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
				/*if ((tokenType1 == "READ") || (tokenType1 == "PRINT")) {
					ReadPrintExtractor readPrintExtractor;
					std::string variableName = readPrintExtractor.extractAbstraction(currentNode);
					if ((tokenType1 == "READ") && (variableName != "")) {
						PKB pkbinstance = PKB();
						pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, procedureName));
					}
					else if ((tokenType1 == "PRINT") && (variableName != "")) {
						PKB pkbinstance = PKB();
						pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", variableName, procedureName));
						//change to USES later
					}

				}*/
				if (tokenType1 == "STATEMENT_LIST") {
					StmtlstExtractor stmtlstExtractor;
					stmtlstExtractor.extractAbstraction(currentNode);
					//parentVector = stmtlstExtractor.extractAbstraction(currentNode, parentVector);
					/*int noOfChildren = (currentNode.children).size();
					for (int j = 0; j < noOfChildren; j++) {
						std::vector<TNode> childNodes = currentNode.children;
						queue1.push(childNodes[j]);
					}*/
				}
				else {}

			}
			queue1.pop();


			
		}
	}
};
