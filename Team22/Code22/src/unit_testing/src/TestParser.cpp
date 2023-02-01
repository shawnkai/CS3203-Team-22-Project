//
// Created by Yi Zhang on 30/1/23.
//
#include "TNode.h"
#include "Parser.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("SPACE SEPARATED ONE LINE PROGRAMME"){
    std::string programme = R"(x = 1 ;)";
    std::vector<std::string>  out(0);
    auto result = Parse(programme, out);
    REQUIRE(out.size() == 4);
}

TEST_CASE("DUMMY TEST CASE") {
    int result = dummy();
    REQUIRE(result == 0);
}
