//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignPatternDatabaseFactory.h"

using namespace std;

AssignPatternDatabase *AssignPatternDatabaseFactory::getAssignPatternDatabase() {
    return assignPatternDatabase;
}

void AssignPatternDatabaseFactory::clearDatabase() {
    delete assignPatternDatabase;

    assignPatternDatabase = new AssignPatternDatabase();
}
