#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

#include "DesignExtractor.h"

#include "../../PKB/PKB.h"



void DesignExtractor::extractAbstraction(TNode root, PKB pkbinstance) {
	AbstractionExtractor abstractionExtractor;
	abstractionExtractor.extractAbstraction(root, pkbinstance);
};

