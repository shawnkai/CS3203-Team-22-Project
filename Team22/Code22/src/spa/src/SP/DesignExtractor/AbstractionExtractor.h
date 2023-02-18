#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "../../PKB/PKB.h"
#include "StmtlstExtractor.h"
#include "SP/Parser/TNode.h"

using namespace std;

class AbstractionExtractor {
public:
	AbstractionExtractor() {};
	void extractAbstraction(TNode root);
};