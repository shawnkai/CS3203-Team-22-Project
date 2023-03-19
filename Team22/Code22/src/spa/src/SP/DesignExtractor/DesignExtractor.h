#ifndef SPA_DESIGNEXTRACTOR_H
#define SPA_DESIGNEXTRACTOR_H


#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "../../PKB/PKB.h"
#include "ProgramExtractor.h"
#include "SP/Parser/TNode.h"

using namespace std;

class DesignExtractor {
public:
	DesignExtractor() {};
	void extractAbstraction(TNode root, PKB pkbinstance);
};
#endif //SPA_DESIGNEXTRACTOR_H
