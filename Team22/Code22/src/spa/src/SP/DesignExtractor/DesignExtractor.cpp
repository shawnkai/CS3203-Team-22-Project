#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

#include "DesignExtractor.h"

#include "../../PKB/PKB.h"

/**
 * Creates an instance of AbstractionExtractor and calls the method of the AbstractionExtractor
 * to extract the abstractions and entities from the Abstract Syntax Tree and
 * add the abstractions and entities to the Program Knowledge Base.
 *
 * @param root The root node of the Abstract Syntax Tree, of type TNode.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void DesignExtractor::extractAbstraction(TNode root, PKB pkbinstance) {
    std::map<string, vector<string>> information;
    ExtractorFactory factory1;
    auto programExtractor = factory1.createExtractor(root, information, pkbinstance);
    programExtractor->extractAbstraction();
    programExtractor->extractCallAbstraction(pkbinstance);
};

