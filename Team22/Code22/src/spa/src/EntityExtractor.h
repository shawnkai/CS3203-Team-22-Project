#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "TNode.h"
#include "VariableExtractor.h"
#include "PKB.h"

using namespace std;

class EntityExtractor {
public:
	void extractEntity(TNode root);
};