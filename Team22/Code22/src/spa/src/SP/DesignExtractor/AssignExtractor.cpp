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

void AssignExtractor::extractAbstraction(TNode currentNode, std::vector<int> ifContainers, std::vector<int> whileContainers, PKB pkbinstance) {
	std::string nodeType1 = ToString(currentNode.nodeType);

	if (nodeType1 != "ASSIGN") {
	}
	else {
		queue<TNode> queue1;
		int firstTime = 0;
		queue1.push(currentNode);
		while (queue1.size() != 0) {
			TNode currentNode1 = queue1.front();
			std::string tokenType1 = ToString(currentNode1.nodeType);
			if (tokenType1 == "NAME_IDENTIFIER") {
				std::string nameOfVariable = currentNode1.stringId;
				int lineNumOfVariable = currentNode1.stmtNumber;
				cout << currentNode1.stringId << endl;
				if (firstTime == 0) {
					firstTime = 1;
					//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("ASSIGN", nameOfVariable, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", nameOfVariable, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
					if (whileContainers.size() != 0) {
						for (int j = 0; j < whileContainers.size(); j++) {
							cout << std::to_string(whileContainers[j]) << endl;
							//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("WHILE", nameOfVariable, std::to_string(whileContainers[j])));
						}
					}
					if (ifContainers.size() != 0) {
						for (int i = 0; i < ifContainers.size(); i++) {
							cout << std::to_string(ifContainers[i]) << endl;
							//pkbinstance.addDesignAbstraction("MODIFIES", make_tuple("IF", nameOfVariable, std::to_string(ifContainers[i])));
						}
					}

				}
				else {
					//pkbinstance.addDesignAbstraction("USES", make_tuple("STATEMENT", nameOfVariable, std::to_string(lineNumOfVariable)));
					pkbinstance.addDesignEntity("VARIABLE", make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
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

	}
};