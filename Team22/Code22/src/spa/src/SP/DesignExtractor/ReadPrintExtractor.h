#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "../TNode.h"
#include "../../PKB/PKB.h"

using namespace std;

class ReadPrintExtractor {
public:
	ReadPrintExtractor() {};
	std::string extractAbstraction(TNode currentNode);
};