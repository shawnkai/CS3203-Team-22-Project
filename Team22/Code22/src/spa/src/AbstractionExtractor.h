#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "PKB.h"
#include "ReadExtractor.h"
#include "TNode.h"


using namespace std;

class AbstractionExtractor {
public:
	void extractAbstraction(TNode root);
};