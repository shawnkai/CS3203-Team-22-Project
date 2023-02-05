#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;


#include "PKB.h"
#include "AbstractionExtractor.h"
#include "EntityExtractor.h"
#include "TNode.h"

/*int DesignExtractor() {
	return 0;
}*/

class DesignExtractor {
	//AbstractionExtractor abstractionExtractor;
	//EntityExtractor entityExtractor;
public:
	DesignExtractor() {

	};
	void extractAbstraction(TNode root) {
		AbstractionExtractor abstractionExtractor;
		abstractionExtractor.extractAbstraction(root);
	}

	void extractEntity(TNode root) {
		EntityExtractor entityExtractor;
		entityExtractor.extractEntity(root);
	}

};