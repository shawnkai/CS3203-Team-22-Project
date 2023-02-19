//
// Created by Jai Lulla  on 15/2/23.
//

#include <iostream>

#include "AssignPatternDatabaseFactory.h"

using namespace std;

/**
 * Returns the database, that stores all the Assignment Patterns.
 *
 * @return A AssignPatternDatabase pointer, that points to the Assignment Patterns database.
 */
AssignPatternDatabase *AssignPatternDatabaseFactory::getAssignPatternDatabase() {
    return assignPatternDatabase;
}

/*
 * Clears the Assignment Patterns database.
 */
void AssignPatternDatabaseFactory::clearDatabase() {
    delete assignPatternDatabase;

    assignPatternDatabase = new AssignPatternDatabase();
}
