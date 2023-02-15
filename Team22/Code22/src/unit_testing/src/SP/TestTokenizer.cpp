//
// Created by Yi Zhang on 14/2/23.
//
#include "SP/Tokenizer.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "catch.hpp"

// NOTE: This test cases' relative path is written for a MAC OS machine, it will break on a Windows Machine.
// Thus, it should be commented out when pushing to GitHib.
//TEST_CASE("Test smallest procedure") {
//    Tokenizer tk = Tokenizer();
//    std::vector<Token> tokenList;
//    try {
//        tokenList = tk.tokenize("../../../SPUnitTestingResources/SP_Tokenizer_ut1.txt");
//    } catch (std::invalid_argument& e) {
//        std::cerr << e.what() << std::endl;
//    }
//    REQUIRE(tokenList.size() == 7);
//}