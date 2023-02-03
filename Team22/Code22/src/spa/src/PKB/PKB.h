#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Result.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:

	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

    void addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails);
    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query); // string -> Result
    Result getDesignEntity(string entityType, string entityName); // string -> Result
    Result getDesignEntity(string entityType, string entityName, string occurrenceLine);
};
