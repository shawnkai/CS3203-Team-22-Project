#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


using namespace std;

#include "AssignExtractor.h"

/**
 * Extracts the abstractions and entities from an assignment statement and
 * adds the abstractions and entities to the Program Knowledge Base. If the assignment 
 * statement is nested in if or while statements, then the related abstractions
 * would also be added to the Program Knowledge Base.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that this assignment statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that this assignment statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void AssignExtractor::extractAbstraction() {
    TokenType nodeType1 = currentNode.nodeType;

    if (nodeType1 != TokenType::ASSIGN) {
        cout << "something went wrong" << endl;
    } else {
        pkbinstance.addDesignEntity("ASSIGNMENT", make_tuple(currentNode.stringId, std::to_string(currentNode.stmtNumber)));
        PatternPrefixStringExtractor prefixExtractor;
        prefixExtractor.extractPrefixString(currentNode, pkbinstance);
        queue<TNode> queue1;
        int firstTime = 0;
        queue1.push(currentNode);
        while (queue1.size() != 0) {
            TNode currentNode1 = queue1.front();
            TokenType tokenType1 = currentNode1.nodeType;
            if (tokenType1 == TokenType::NAME_IDENTIFIER) {
                std::string nameOfVariable = currentNode1.stringId;
                int lineNumOfVariable = currentNode1.stmtNumber;
                pkbinstance.addDesignEntity(assignmentStr, make_tuple(assignmentStr, std::to_string(lineNumOfVariable)));
                pkbinstance.addDesignEntity(statementStr, make_tuple(statementStr, std::to_string(lineNumOfVariable)));
                cout << currentNode1.stringId << endl;
                if (firstTime == 0) {
                    firstTime = 1;
                    pkbinstance.addDesignAbstraction(modifiesStr, make_tuple(assignmentStr, nameOfVariable, std::to_string(lineNumOfVariable)));
                    pkbinstance.addDesignAbstraction(modifiesStr, make_tuple(statementStr, nameOfVariable, std::to_string(lineNumOfVariable)));
                    RelationshipExtractor relationshipExtractor;
                    relationshipExtractor.extractModifiesorUsesAbstraction(modifiesStr, pkbinstance, procedureName, nameOfVariable, lineNumOfVariable);
                    relationshipExtractor.extractContainerUsesOrModifiesAbstraction(modifiesStr, ifContainers, whileContainers, pkbinstance, nameOfVariable);
                    pkbinstance.addDesignEntity(variableStr, make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));

                } else {
                    pkbinstance.addDesignAbstraction(usesStr, make_tuple(assignmentStr, nameOfVariable, std::to_string(lineNumOfVariable)));
                    pkbinstance.addDesignAbstraction(usesStr, make_tuple(statementStr, nameOfVariable, std::to_string(lineNumOfVariable)));
                    RelationshipExtractor relationshipExtractor;
                    relationshipExtractor.extractModifiesorUsesAbstraction(usesStr, pkbinstance, procedureName, nameOfVariable, lineNumOfVariable);
                    relationshipExtractor.extractContainerUsesOrModifiesAbstraction(usesStr, ifContainers, whileContainers, pkbinstance, nameOfVariable);
                    pkbinstance.addDesignEntity(variableStr, make_tuple(nameOfVariable, std::to_string(lineNumOfVariable)));
                    
                }

            } else if (tokenType1 == TokenType::OPERATOR) {
                std::vector<TNode> childNodes = currentNode1.children;
                for (int i = 0; i < childNodes.size(); i++) {
                    queue1.push(childNodes[i]);
                }
            } else if (tokenType1 == TokenType::ASSIGN) {
                std::vector<TNode> childNodes = currentNode1.children;
                for (int i = 0; i < childNodes.size(); i++) {
                    queue1.push(childNodes[i]);
                }
            } else if (tokenType1 == TokenType::INTEGER) {
                std::string stringOfConstant = currentNode1.stringId;
                pkbinstance.addDesignEntity(constantStr, make_tuple(stringOfConstant, std::to_string(currentNode1.stmtNumber)));

            } else {
            }
            queue1.pop();
        }
    }
};