#include "SP/DesignExtractor/AbstractionExtractor.h"
#include "catch.hpp"
using namespace std;
TEST_CASE("Testcase1_ExtractOneStatement_ShouldSuccess") {

	TNode read1 = TNode(TokenType::READ, "x", 1, std::vector<TNode>(0));
	TNode stmtlist1 = TNode(TokenType::STATEMENT_LIST, "stmtList", 1, std::vector<TNode>(0));
	std::vector<TNode> child;
	child.push_back(read1);
	stmtlist1.children = child;
	TNode root = TNode(TokenType::PROCEDURE, "main", 0, std::vector<TNode>(0));

	PKB pkbinstance = PKB();
	AbstractionExtractor abstractionExtractor;

	abstractionExtractor.extractAbstraction(root, pkbinstance);
}