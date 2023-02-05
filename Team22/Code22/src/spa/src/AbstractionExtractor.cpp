#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

#include "PKB.h"
#include "ReadExtractor.h"
#include "TNode.h"

class AbstractionExtractor {
	//ReadExtractor readExtractor;
public:
	AbstractionExtractor() {

	};

	void extractAbstraction(TNode root) {
		ReadExtractor readExtractor;
		return readExtractor.extractAbstraction(root);
	}
};