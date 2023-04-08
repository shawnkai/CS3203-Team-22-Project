#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

// Remove These After clearAllDatabases has been removed;
#include "PKB/Pattern/AssignPattern/AssignPatternDatabaseManager.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"
#include "PKB/ControlFlowGraph/ControlFlowGraphDatabaseManager.h"
#include "PKB/Pattern/PatternsDatabaseFactory.h"

/**
 * This method allows to add a Design Abstraction to the Program Knowledge Base.
 *
 * @param designAbstraction The type of Abstraction that is to be added.
 * @param abstractionDetails A tuple, which takes in 3 strings. which contains the details about the Abstraction.
 */
void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails) {
    this->designAbstractionsInterface->addDesignAbstraction(designAbstraction, abstractionDetails);
}

/**
 * This method allows to add a Design Entity to the Program Knowledge Base.
 *
 * @param designEntity The type of Design Entity that is to be added.
 * @param entityDetails A tuple, which takes in 2 strings, which contains the details about the Design Entity.
 */
void PKB::addDesignEntity(string designEntity, tuple<string, string> entityDetails) {
    this->designEntitiesInterface->addDesignEntity(designEntity, entityDetails);
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
    return this->designAbstractionsInterface->getDesignAbstraction(abstractionType, query);
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
    return this->designEntitiesInterface->getDesignEntity(entityType, entityName);
}

/**
 * Returns a vector<Result>, containing all the Design Entity Details of that
 * Design Entity Type.
 *
 * @param entityType The type of Design Entity to obtain.
 * @return A vector<Result> with each Result Object containing the details of that Design Entity type.
 */
vector<Result> PKB::getAllDesignEntity(string entityType) {
    return this->designEntitiesInterface->getAllDesignEntity(entityType);
}

/**
 * This method allows to add an Assignment Pattern to the Program Knowledge Base.
 *
 * @param leftHandVariableName The name of the variable that is being assigned to.
 * @param prefixExpression The expression on the right hand side, which has been converted into its prefix form.
 * @param patternLineNumber The line number at which this assignment pattern can be observed.
 */
void PKB::addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber) {
    this->patternsInterface->addAssignPattern(leftHandVariableName, prefixExpression, patternLineNumber);
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
    return this->patternsInterface->getRightHandExpressionOfAVariableOnAParticularLineNumber(leftHandVariableName,
                                                                                             patternLineNumber);
}

/**
 * Returns an unordered map containing all the Right Hand Prefix Expression associated to a given
 * variable, that would have occurred on the left hand side.
 *
 * @param leftHandVariableName The variable, which has been assigned, to be looked for.
 * @return An unordered map containing all the Right Hand Prefix Expressions associated to the given variable.
 */
unordered_map<string, string> PKB::getAllRightHandExpressionsOfAVariable(string leftHandVariableName) {
    return this->patternsInterface->getAllRightHandExpressionsOfAVariable(leftHandVariableName);
}

/**
 * Returns a vector of AssignPattern pointer objects, that contain all the patterns derivable from
 * the assignment statements. This is particularly useful, when wildcards come into play.
 *
 * @return A vector of AssignPattern pointer objects, or an empty vector, if nothing is stored.
 */
unordered_map<string, unordered_map<string, string>> PKB::getAllRightHandExpressions() {
    return this->patternsInterface->getAllRightHandExpressions();
}

vector<Result> PKB::getAllDesignAbstractions(string designAbstractionType, string entityTypeBeingAbstracted) {
    return this->designAbstractionsInterface->getAllDesignAbstractions(designAbstractionType,
                                                                       entityTypeBeingAbstracted);
}

unordered_map<string, unordered_set<string>>
PKB::getAllVariablesCapturedByDesignAbstraction(string designAbstractionType, string entityTypeBeingAbstracted) {
    return this->designAbstractionsInterface->getAllVariablesCapturedByDesignAbstraction(designAbstractionType,
                                                                                         entityTypeBeingAbstracted);
}

int PKB::getNumberOfDesignEntity(string entityType) {
    return this->designEntitiesInterface->getNumberOfDesignEntity(entityType);
}

void PKB::addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails) {
    this->designAbstractionsInterface->addDesignAbstraction(designAbstraction, abstractionDetails);
}

Result PKB::getDesignAbstraction(string abstractionType, string query) {
    return this->designAbstractionsInterface->getDesignAbstraction(abstractionType, query);
}

void PKB::addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                              unordered_map<int, vector<int>> blockToStatementNumbers,
                              unordered_map<int, int> statementNumberToBlock,
                              unordered_map<int, vector<int>> blockToBlock,
                              unordered_set<int> blocksWithBackPointers) {
    this->controlFlowGraphInterface->addControlFlowGraph(procedureName, topologicallySortedElements,
                                                         blockToStatementNumbers, statementNumberToBlock,
                                                         blockToBlock, blocksWithBackPointers);
}

vector<int> PKB::getTopologicallySortedElementsDatabase(string procedureName) {
    return this->controlFlowGraphInterface->getTopologicallySortedElementsDatabase(procedureName);
}

unordered_map<int, vector<int>> PKB::getBlockToStatementNumbersDatabase(string procedureName) {
    return this->controlFlowGraphInterface->getBlockToStatementNumbersDatabase(procedureName);
}

unordered_map<int, int> PKB::getStatementNumberToBlockDatabase(string procedureName) {
    return this->controlFlowGraphInterface->getStatementNumberToBlockDatabase(procedureName);
}

unordered_map<int, vector<int>> PKB::getBlockToBlockDatabase(string procedureName) {
    return this->controlFlowGraphInterface->getBlockToBlockDatabase(procedureName);
}

unordered_set<int> PKB::getBlocksWithBackPointersDatabase(string procedureName) {
    return this->controlFlowGraphInterface->getBlocksWithBackPointersDatabase(procedureName);
}

void PKB::addPattern(string patternType, string lineNumber, string variableName) {
    this->patternsInterface->addPattern(patternType, lineNumber, variableName);
}

bool PKB::isVariableUsedInPattern(string patternType, string lineNumber, string variableName) {
    return this->patternsInterface->isVariableUsedInPattern(patternType, lineNumber, variableName);
}

unordered_set<string> PKB::getAllVariablesUsedInPattern(string patternType, string lineNumber) {
    return this->patternsInterface->getAllVariablesUsedInPattern(patternType, lineNumber);
}

void PKB::addToCache(string accessKey, ResultTable *resultTable) {
    this->cacheInterface->addToCache(accessKey, resultTable);
}

ResultTable *PKB::getResultTableFromCache(string accessKey) {
    return this->cacheInterface->getResultTableFromCache(accessKey);
}

unordered_map<string, ResultTable *> PKB::getCacheDatabase() {
    return this->cacheInterface->getCacheDatabase();
}

void PKB::clearCache() {
    this->cacheInterface->clearCache();
}

/**
 * Clears the Assignment Pattern Database. This method is hidden
 * from the user.
 */
void PKB::clearAssignPatternDatabase() {
    AssignPatternDatabaseManager::clearDatabase();
}

/**
 * Clears the Design Entities Database. This method is hidden
 * from the user.
 */
void PKB::clearDesignEntityDatabase() {
    DesignEntitiesDatabaseFactory::clearDatabase();
}

/**
 * Clears the Design Abstractions Database. This method is hidden
 * from the user.
 */
void PKB::clearDesignAbstractionDatabase() {
    DesignAbstractionsDatabaseFactory::clearDatabase();
}

void PKB::clearControlFlowGraphDatabase() {
    ControlFlowGraphDatabaseManager::clearDatabase();
}

void PKB::clearPatternDatabase() {
    PatternsDatabaseFactory::clearDatabase();
}

/**
 * Clears the databases. Implemented to improve testing, as PKB storage is
 * static in nature, and to avoid cross-linkage among test cases.
 */
void PKB::clearAllDatabases() {
    this->clearDesignAbstractionDatabase();
    this->clearDesignEntityDatabase();
    this->clearAssignPatternDatabase();
    this->clearControlFlowGraphDatabase();
    this->clearPatternDatabase();
}
