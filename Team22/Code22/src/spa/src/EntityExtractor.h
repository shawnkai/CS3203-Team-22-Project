#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "TNode.h"
#include "VariableExtractor.h"
#include "PKB/PKB.h"

using namespace std;

class EntityExtractor {
public:
	EntityExtractor() {};
	void extractEntity(TNode root);
};