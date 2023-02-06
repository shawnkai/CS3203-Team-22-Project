#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;

#include "DesignExtractor.h"

/*#include "PKB.h"
#include "AbstractionExtractor.h"
#include "EntityExtractor.h"
#include "TNode.h"*/
#include "PKB/PKB.h"

/*int DesignExtractor() {
	return 0;
}*/

//class DesignExtractor {
	//AbstractionExtractor abstractionExtractor;
	//EntityExtractor entityExtractor;
//public:
	//DesignExtractor() {

	//};

void DesignExtractor::extractAbstraction(TNode root) {
	AbstractionExtractor abstractionExtractor;
	abstractionExtractor.extractAbstraction(root);
};

void DesignExtractor::extractEntity(TNode root) {
	EntityExtractor entityExtractor;
	entityExtractor.extractEntity(root);
};

//};