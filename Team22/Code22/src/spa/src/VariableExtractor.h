#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "TNode.h"
#include "PKB.h"

using namespace std;

class VariableExtractor {
public:
	VariableExtractor() {};
	void extractEntity(TNode root);
};