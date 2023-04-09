#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <utility>


using namespace std;

#include "ReadPrintExtractor.h"

/**
 * Extracts the abstractions and entities from a read statement or a print statement, and adds
 * the abstractions and entities to the Program Knowledge Base. If the current statement is 
 * nested in other if or while statements, then the related abstractions would also be added
 * to the Program Knowledge Base.
 *
 * @param currentNode The current node in the Abstract Syntax Tree, of type TNode.
 * @param ifContainers The vector of line numbers of the if statements that the current statement is nested in.
 * @param whileContainers The vector of line numbers of the while statements that the current statement is nested in.
 * @param pkbinstance An instance of Program Knowledge Base.
 * @param procedureName The name of the procedure.
 */
void ReadPrintExtractor::extractAbstraction() {

	if (currentNode.nodeType == TokenType::UNKNOWN) {
		cout << "something went wrong" << endl;
	}
	else {
		TokenType tokenType1 = currentNode.nodeType;
		std::vector<TNode> childNodes = currentNode.children;
		TNode childNode = childNodes[0];
		std::string variableName = childNode.stringId;
		int lineNumOfVariable = childNode.stmtNumber;
		cout << variableName << endl;

		if (tokenType1 == TokenType::READ) {
            pkbinstance.addDesignEntity(readStr, make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity(statementStr, make_tuple(variableName, std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(modifiesStr, make_tuple(readStr, variableName, std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(modifiesStr, make_tuple(statementStr, variableName, std::to_string(lineNumOfVariable)));
            RelationshipExtractor relationshipExtractor;
            relationshipExtractor.extractModifiesorUsesAbstraction(modifiesStr, pkbinstance, procedureName, variableName, lineNumOfVariable);
            relationshipExtractor.extractContainerUsesOrModifiesAbstraction(modifiesStr, ifContainers, whileContainers, pkbinstance, variableName);
            pkbinstance.addDesignEntity(variableStr, make_tuple(variableName, std::to_string(lineNumOfVariable)));
		}
		else if (tokenType1 == TokenType::PRINT) {
            pkbinstance.addDesignEntity(printStr, make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity(statementStr, make_tuple(variableName, std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(usesStr, make_tuple(printStr, variableName, std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(usesStr, make_tuple(statementStr, variableName, std::to_string(lineNumOfVariable)));
            RelationshipExtractor relationshipExtractor;
            relationshipExtractor.extractModifiesorUsesAbstraction(usesStr, pkbinstance, procedureName, variableName, lineNumOfVariable);
            relationshipExtractor.extractContainerUsesOrModifiesAbstraction(usesStr, ifContainers, whileContainers, pkbinstance, variableName);
			
			pkbinstance.addDesignEntity(variableStr, make_tuple(variableName, std::to_string(lineNumOfVariable)));
			

		}
		else {
		}
			
	}
};