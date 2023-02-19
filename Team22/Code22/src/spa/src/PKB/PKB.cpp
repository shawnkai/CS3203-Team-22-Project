#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"

#include "DesignAbstractions/DesignAbstractionsFactory.h"
#include "DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

#include "DesignEntities/DesignEntitiesFactory.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

#include "Pattern/AssignPattern/AssignPatternFactory.h"
#include "Pattern/AssignPattern/AssignPatternDatabaseFactory.h"

/**
 * This method allows to add a Design Abstraction to the Program Knowledge Base.
 *
 * @param designAbstraction The type of Abstraction that is to be added.
 * @param abstractionDetails A tuple, which takes in 3 strings. which contains the details about the Abstraction.
 */
void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails) {
    DesignAbstraction* da = DesignAbstractionsFactory::createDesignAbstraction(designAbstraction, abstractionDetails);
    da->addToDatabase();
}

/**
 * This method allows to add a Design Entity to the Program Knowledge Base.
 *
 * @param designEntity The type of Design Entity that is to be added.
 * @param entityDetails A tuple, which takes in 2 strings, which contains the details about the Design Entity.
 */
void PKB::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    DesignEntity* de = DesignEntitiesFactory::createDesignEntity(designEntity, entityDetails);
    de->addToDatabase();
}

/**
 * Returns a Result Object, containing the Design Abstraction Details. These can
 * be accessed by the Result methods to be acted upon further.
 *
 * @param abstractionType Type of Abstraction to obtain.
 * @param query Query contains the Design Entity type being abstracted along with the Entity Name.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result PKB::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    DesignAbstractionDatabase* db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(abstractionType,
                                                                                              get<0>(query));
    Result queryResult = db->getFromDatabase(get<1>(query));

    return queryResult;
}

/**
 * Returns a Result Object, containing the Design Entity Details. These can be
 * accessed by the Result methods to be acted upon further.
 *
 * @param entityType Type of Entity to obtain.
 * @param entityName The name of the Design Entity to be extracted.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result PKB::getDesignEntity(string entityType, string entityName) {
    DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    Result queryResult = db->getFromDatabase(entityName);

    return queryResult;
}

/**
 * Returns a vector<Result>, containing all the Design Entity Details of that
 * Design Entity Type.
 *
 * @param entityType The type of Design Entity to obtain.
 * @return A vector<Result> with each Result Object containing the details of that Design Entity type.
 */
vector<Result> PKB::getAllDesignEntity(string entityType) {
    vector<Result> queryResult;

    DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase(entityType);
    queryResult = db->getAllFromDatabase();

    return queryResult;
}

/**
 * This method allows to add an Assignment Pattern to the Program Knowledge Base.
 *
 * @param leftHandVariableName The name of the variable that is being assigned to.
 * @param prefixExpression The expression on the right hand side, which has been converted into its prefix form.
 * @param patternLineNumber The line number at which this assignment pattern can be observed.
 */
void PKB::addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber) {
    AssignPattern* assignPattern = AssignPatternFactory::createAssignPattern(leftHandVariableName, prefixExpression,
                                                                             patternLineNumber);
    assignPattern->addToDatabase();
}

/**
 * Returns a string containing the Right Hand Prefix Expression, for the given left hand variable name
 * and line number, else returns an empty string, if any pattern stored for the given combinations
 * cannot be found.
 *
 * @param leftHandVariableName The variable, which has been assigned, to be looked for.
 * @param patternLineNumber The line number at which this assignment took place.
 * @return A string containing the Right Hand Prefix Expression or an empty string.
 */
string
PKB::getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName, string patternLineNumber) {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase
    ->getRightHandExpressionOfAVariableOnAParticularLineNumberFromDatabase(leftHandVariableName, patternLineNumber);
}

/**
 * Returns an unordered map containing all the Right Hand Prefix Expression associated to a given
 * variable, that would have occurred on the left hand side.
 *
 * @param leftHandVariableName The variable, which has been assigned, to be looked for.
 * @return An unordered map containing all the Right Hand Prefix Expressions associated to the given variable.
 */
unordered_map<string, string> PKB::getAllRightHandExpressionsOfAVariable(string leftHandVariableName) {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase->getAllRightHandExpressionsOfAVariableFromDatabase(leftHandVariableName);
}

/**
 * Returns a vector of AssignPattern pointer objects, that contain all the patterns derivable from
 * the assignment statements. This is particularly useful, when wildcards come into play.
 *
 * @return A vector of AssignPattern pointer objects, or an empty vector, if nothing is stored.
 */
vector<AssignPattern*> PKB::getAllRightHandExpressions() {
    AssignPatternDatabase* assignPatternDatabase = AssignPatternDatabaseFactory::getAssignPatternDatabase();
    return assignPatternDatabase->getAllRightHandExpressionsFromDatabase();
}

void PKB::clearAssignPatternDatabase() {
    AssignPatternDatabaseFactory::clearDatabase();
}

void PKB::clearDesignEntityDatabase() {
    DesignEntitiesDatabaseFactory::clearDatabase();
}

void PKB::clearDesignAbstractionDatabase() {
    DesignAbstractionsDatabaseFactory::clearDatabase();
}

void PKB::clearAllDatabases() {
    this->clearDesignAbstractionDatabase();
    this->clearDesignEntityDatabase();
    this->clearAssignPatternDatabase();
}
