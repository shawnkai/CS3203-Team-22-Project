#include "SP/TNode.h"
#include "catch.hpp"
using namespace std;
void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("TestCase1_Constructor_ShouldSuccess") {
    TNode T;

    require(T.stringId.empty());
    require(T.stmtNumber == 0);
    require(T.children.empty());
    require(T.nodeType == TokenType::UNKNOWN);
}

TEST_CASE("TestCase2_TNodeToString_ShouldSuccess") {
    TNode t;
    t.nodeType = TokenType::NAME_IDENTIFIER;
    t.stringId = "testingId";
    t.children.push_back(TNode(TokenType::INTEGER, "1", 1, {}));
    t.stmtNumber = 1;
    string result = ToString(t);

    require(result == "NAME_IDENTIFIERtestingId1 with children: 1");
}
