
#include "PatternPrefixStringExtractor.h"
using namespace std;

/**
 * Extract the prefix representation of an assignment node, include left-hand side and right-hand side.
 *
 * @param root an AST representation of an assignment statement
 * @param instance the PKB entry point for storage
 */
void PatternPrefixStringExtractor::extractPrefixString(TNode root, PKB instance) {

    TNode lhs = root.children[0];
    TNode rhs = root.children[1];
    string lhsString = lhs.stringId;
    string stmtNumber = to_string(root.stmtNumber);
    string rhsString = handlePrefixGeneration(rhs, "");
    cout << lhsString << " " << rhsString << " " << endl;
    instance.addAssignPattern(lhsString, rhsString, stmtNumber);
}

/**
 * Recursively build the prefix string of a potentially complex arithmetic expression.
 *
 * @param node an AST representation of an arithmetic expression of type OPERATOR
 * @param result result from the base/previous recursion call
 * @return  a prefix string represents the arithmetic expression
 */
string PatternPrefixStringExtractor::handlePrefixGeneration(TNode node, string result) {
    auto myChildren = node.children;
    bool isTerminalOperator = true;
    for (TNode checker: myChildren) {
        isTerminalOperator = (isTerminalOperator &&
                              (checker.nodeType == TokenType::NAME_IDENTIFIER || checker.nodeType == TokenType::INTEGER));
    }
    if (isTerminalOperator) {
        string childrenCombined;
        for (TNode checker: myChildren) {
            childrenCombined += checker.stringId;
        }
        result = result + node.stringId + childrenCombined;
        return result;
    } else {
        TNode lhs = node.children[0];
        TNode rhs = node.children[1];
        if (rhs.nodeType == TokenType::NAME_IDENTIFIER || rhs.nodeType == TokenType::INTEGER) {
            result = node.stringId + handlePrefixGeneration(lhs, result) + rhs.stringId;
        } else if (lhs.nodeType == TokenType::NAME_IDENTIFIER || rhs.nodeType == TokenType::INTEGER) {
            result = node.stringId + lhs.stringId + handlePrefixGeneration(rhs, result);
        } else {
            result = node.stringId + handlePrefixGeneration(lhs, result) + handlePrefixGeneration(rhs, result);
        }
        return result;
    }
}
