//
// Created by Yi Zhang on 19/3/23.
//
#include "catch.hpp"
#include <filesystem>
#include "SP/Parser/Parser.h"
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Cfg/Cfg.h"

TEST_CASE("TestCase1_TestCfgComplexSingleSource_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;

    relativePath = "SP_ut_cfg_1.txt";

    string code = "procedure Example {\n"
                  " x = 2;\n"
                  " while (i!=0) {\n"
                  "   if (x > 1) then {\n"
                  "     z = x + 1; }\n"
                  "   else {\n"
                  "     y = z + x;\n"
                  "     if (x >= 5) then {\n"
                  "        z = x + 1;\n"
                  "        while ( x < 10) {\n"
                  "           x = x - 1;\n"
                  "           while ((x <= 9) || ((z % 2) == 1)) {\n"
                  "             anx = 1;\n"
                  "             if (z == 1) then {\n"
                  "               z = 2;\n"
                  "             } else {\n"
                  "               z = 3;\n"
                  "               while (!(!(j < 0))) {\n"
                  "                 j = ((1 + 2) * (3 + 4) + 5) % 6 / 7 ;\n"
                  "               }\n"
                  "             }\n"
                  "           }\n"
                  "        }\n"
                  "     }\n"
                  "     else {\n"
                  "       print x;\n"
                  "     }\n"
                  "   }\n"
                  " }\n"
                  "}";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    TNode largest = result.children[0];
    Cfg builder = Cfg(largest);
    builder.buildCfg(largest, -1);

    REQUIRE(builder.basicBlock.size() == 17);
    REQUIRE(builder.blockPointingBackward.size() == 4);
    REQUIRE(builder.blockGraph.size() == 17);
    REQUIRE(builder.blockToStatement.size() == 17);
    REQUIRE(builder.statementNumberToBlock.size() == 17);
}

TEST_CASE("TestCase2_TestCfgMultipleProcedures_ShouldSuccess") {
    Tokenizer tk = Tokenizer();
    std::vector<Token> tokenList;
    const char *relativePath;
    relativePath = "SP_ut22.txt";

    string code = "procedure TestFollows {\n"
                  "  x = 1;\n"
                  "  print y;\n"
                  "  while (z>2) {\n"
                  "    read z;\n"
                  "    print k;\n"
                  "    if (a < 2) then {\n"
                  "      read y;\n"
                  "    } else {\n"
                  "      k = k + 1;\n"
                  "      while (b <= 6) {\n"
                  "        read a;\n"
                  "        while (c > 3) {\n"
                  "        if (d > a) then {\n"
                  "           z = 1;\n"
                  "        } else {\n"
                  "          print z;\n"
                  "          read b;\n"
                  "        }\n"
                  "       }\n"
                  "      }\n"
                  "      }\n"
                  "      y = a - 1;\n"
                  "      }\n"
                  "      if (z > 1) then {\n"
                  "        read k;\n"
                  "      }\n"
                  "       else {\n"
                  "         while (x > 2) {\n"
                  "           z = 5;\n"
                  "         }\n"
                  "                      while (y <= 9) {\n"
                  "                        print y;\n"
                  "                        print x;\n"
                  "                        if (a > 5) then {\n"
                  "                          while (a >6) {\n"
                  "                              a = a + 1;\n"
                  "                              print a;\n"
                  "                              while (z > 3) {\n"
                  "                                 read z;\n"
                  "                              }\n"
                  "                           }\n"
                  "                         } else {\n"
                  "                            print s;\n"
                  "                        }\n"
                  "                       }\n"
                  "                    }\n"
                  "                   read z;\n"
                  "}\n"
                  "procedure test2 {\n"
                  "                  read a;\n"
                  "                  }\n"
                  "procedure test3 {\n"
                  "                  read b;\n"
                  "                 }";
    ofstream temp_file;
    temp_file.open(relativePath);
    temp_file << code;
    temp_file.close();

    try {
        tokenList = tk.tokenize(relativePath);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    Parser ps = Parser(tokenList);
    TNode result;
    try {
        result = ps.Parse();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    vector<Cfg> graphs;
    Cfg cfg1 = Cfg(result.children[1]);
    cout << ToString(result) << endl;
    TNode proc1 = result.children[1];
    REQUIRE(proc1.nodeType == TokenType::PROCEDURE);
    cfg1.buildCfg(proc1, -1);
    REQUIRE(cfg1.blockGraph.size() == 1);

    map<int, vector<int> >::iterator itr;
    auto simplestGraph = cfg1.blockGraph;
    itr = simplestGraph.find(1);
    REQUIRE(itr->second.size() == 1);
    REQUIRE(itr->second[0] == 0);
}
