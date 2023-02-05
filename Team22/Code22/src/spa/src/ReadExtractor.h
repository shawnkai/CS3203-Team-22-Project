#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "TNode.h"
#include "PKB.h"

using namespace std;

class ReadExtractor {
public:
	ReadExtractor() {};
	void extractAbstraction(TNode root);
};