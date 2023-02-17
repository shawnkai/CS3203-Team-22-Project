#ifndef SPA_DESIGNEXTRACTOR_H
#define SPA_DESIGNEXTRACTOR_H


// Design Extractor uses the Facade design pattern and is divided into Abstraction Extractor and Entity Extractor
// Both of which implements the extract() method
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "../../PKB/PKB.h"
#include "AbstractionExtractor.h"
//#include "EntityExtractor.h"
#include "SP/Parser/TNode.h"

using namespace std;

class DesignExtractor {
public:
	DesignExtractor() {};
	void extractAbstraction(TNode root);//DesignExtractor::
	void extractEntity(TNode root);
};
#endif //SPA_DESIGNEXTRACTOR_H
