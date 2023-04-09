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
			pkbinstance.addDesignEntity("READ", make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity("STATEMENT", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(readStr, variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, variableName, std::to_string(lineNumOfVariable)));
            RelationshipExtractor relationshipExtractor;
            relationshipExtractor.extractModifiesorUsesAbstraction("MODIFIES", pkbinstance, procedureName, variableName, lineNumOfVariable);
            relationshipExtractor.extractContainerUsesOrModifiesAbstraction("MODIFIES", ifContainers, whileContainers, pkbinstance, variableName);
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
		}
		else if (tokenType1 == TokenType::PRINT) {
			pkbinstance.addDesignEntity("PRINT", make_tuple(variableName, std::to_string(currentNode.stmtNumber)));
            pkbinstance.addDesignEntity("STATEMENT", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple(printStr, variableName, std::to_string(lineNumOfVariable)));
			pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, variableName, std::to_string(lineNumOfVariable)));
            RelationshipExtractor relationshipExtractor;
            relationshipExtractor.extractModifiesorUsesAbstraction("USES", pkbinstance, procedureName, variableName, lineNumOfVariable);
            relationshipExtractor.extractContainerUsesOrModifiesAbstraction("USES", ifContainers, whileContainers, pkbinstance, variableName);
			
			pkbinstance.addDesignEntity("VARIABLE", make_tuple(variableName, std::to_string(lineNumOfVariable)));
			

		}
		else {
		}
			
	}
};