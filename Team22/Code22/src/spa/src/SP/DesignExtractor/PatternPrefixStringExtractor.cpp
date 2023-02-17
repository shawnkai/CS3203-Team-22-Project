
#include "PatternPrefixStringExtractor.h"
using namespace std;

void PatternPrefixStringExtractor::extractPrefixString(TNode root, PKB instance) {
    
    TNode lhs = root.children[0];
    TNode rhs = root.children[1];
    string lhsString = lhs.stringId;
    string stmtNumber = to_string(root.stmtNumber);
    string rhsString = handlePrefixGeneration(rhs, "");
    cout << lhsString << " " << rhsString << " " << endl;
    
}

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
        }
        else if (lhs.nodeType == TokenType::NAME_IDENTIFIER || rhs.nodeType == TokenType::INTEGER) {
            result = node.stringId + lhs.stringId + handlePrefixGeneration(rhs, result);
        }
        else {
            result = node.stringId + handlePrefixGeneration(lhs, result)
                    + handlePrefixGeneration(rhs, result);
        }
        return result;
    }
}

//int main() {
//    Token t1 = Token(INTEGER, "1", 1);
//    Token t2 = Token(INTEGER, "2", 1);
//    Token t3 = Token(INTEGER, "3", 1);
//    Token t4 = Token(INTEGER, "4", 1);
//    Token t5 = Token(OPERATOR, "+", 1);
//    Token t6 = Token(OPERATOR, "+", 1);
//    Token t7 = Token(OPERATOR, "*", 1);
//    Token t8 = Token(INTEGER, "5", 1);
//    Token t9 = Token(NAME_IDENTIFIER, "A", 1);
//    Token t10 = Token(INTEGER, "9", 1);
//    Token t11 = Token(OPERATOR, "+", 1);
//    Token t12 = Token(OPERATOR, "-", 1);
//    Token t13 = Token(OPERATOR, "%", 1);
//    Token t14 = Token(INTEGER, "7", 1);
//    Token t15 = Token(OPERATOR, "/", 1);
//    TNode n1 = TNode(t1.type, t1.value, t1.lineNumber, std::vector<TNode>(0));
//    TNode n2 = TNode(t2.type, t2.value, t2.lineNumber, std::vector<TNode>(0));
//    TNode n3 = TNode(t3.type, t3.value, t3.lineNumber, std::vector<TNode>(0));
//    TNode n4 = TNode(t4.type, t4.value, t4.lineNumber, std::vector<TNode>(0));
//    std::vector<TNode> n5Children;
//    n5Children.push_back(n1);
//    n5Children.push_back(n2);
//    TNode n5 = TNode(t5.type, t5.value, t5.lineNumber, std::vector<TNode>(0));
//    n5.children = n5Children;
//
//    std::vector<TNode> n6Children;
//    n6Children.push_back(n3);
//    n6Children.push_back(n4);
//    TNode n6 = TNode(t5.type, t6.value, t6.lineNumber, std::vector<TNode>(0));
//    n6.children = n6Children;
//
//    std::vector<TNode> n7Children;
//    n7Children.push_back(n5);
//    n7Children.push_back(n6);
//    TNode n7 = TNode(t7.type, t7.value, t7.lineNumber, std::vector<TNode>(0));
//    n7.children = n7Children;
//
//
//    TNode n8 = TNode(t8.type, t8.value, t8.lineNumber, std::vector<TNode>(0));
//
//    TNode n9 = TNode(t9.type, t9.value, t9.lineNumber, std::vector<TNode>(0));
//
//    TNode n10 = TNode(t10.type, t10.value, t10.lineNumber, std::vector<TNode>(0));
//
//    std::vector<TNode> n11Children;
//    n11Children.push_back(n7);
//    n11Children.push_back(n8);
//    TNode n11 = TNode(t11.type, t11.value, t11.lineNumber, std::vector<TNode>(0));
//    n11.children = n11Children;
//
//    std::vector<TNode> n12Children;
//    n12Children.push_back(n9);
//    n12Children.push_back(n10);
//    TNode n12 = TNode(t12.type, t12.value, t12.lineNumber, std::vector<TNode>(0));
//    n12.children = n12Children;
//
//    std::vector<TNode> n13Children;
//    n13Children.push_back(n11);
//    n13Children.push_back(n12);
//    TNode n13 = TNode(t13.type, t13.value, t13.lineNumber, std::vector<TNode>(0));
//    n13.children = n13Children;
//
//
//    TNode n14 = TNode(t14.type, t14.value, t14.lineNumber, std::vector<TNode>(0));
//
//    std::vector<TNode> n15Children;
//    n15Children.push_back(n13);
//    n15Children.push_back(n14);
//    TNode n15 = TNode(t15.type, t15.value, t15.lineNumber, std::vector<TNode>(0));
//    n15.children = n15Children;
//
//    TNode var = TNode(TokenType::NAME_IDENTIFIER, "VAR", 0, std::vector<TNode>(0));
//
//    std::vector<TNode> n17Children;
//    n17Children.push_back(var);
//    n17Children.push_back(n15);
//    TNode n17 = TNode(TokenType::ASSIGN, "=", 0, std::vector<TNode>(0));
//    n17.children = n17Children;
//
//
//    std::vector<TNode> n16Children;
//    n16Children.push_back(n17);
//    TNode n16 = TNode(TokenType::STATEMENT_LIST, "stmtList", 0, std::vector<TNode>(0));
//    n16.children = n16Children;
//    PatternPrefixStringExtractor extractor;
//    extractor.extractPrefixString(n16);
//}