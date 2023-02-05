#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;
#include "VariableExtractor.h"
#include "PKB.h"
#include "TNode.h"


class EntityExtractor {
	//VariableExtractor variableExtractor;
public:
	EntityExtractor() {

	};

	void extractEntity(TNode root) {
		VariableExtractor variableExtractor;
		return variableExtractor.extractEntity(root);
	}
};