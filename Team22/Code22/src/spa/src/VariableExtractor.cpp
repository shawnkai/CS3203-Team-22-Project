#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>


using namespace std;


#include "PKB.h"
#include "TNode.h"


class VariableExtractor {
public:
	void extractEntity(TNode root) {
		if (root.nodeType == UNKNOWN) {
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
				for (int i = size1; i > 0; i--) {
					TNode currentNode = queue1.front();
					queue1.pop();
					TokenType tokenType;
					tokenType = currentNode.nodeType;
					std::string tokenType1 = ToString(tokenType);
					//std::string tokenType1 = currentNode.nodeType;
					if (tokenType1 == "PROCEDURE") {
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


				}
			}
		}
	}
};
