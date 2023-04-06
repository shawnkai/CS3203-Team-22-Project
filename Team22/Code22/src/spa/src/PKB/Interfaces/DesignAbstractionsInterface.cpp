//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "DesignAbstractionsInterface.h"

#include "PKB/DesignAbstractions/DesignAbstractionsFactory.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

/**
 * This method allows to add a Design Abstraction to the Program Knowledge Base.
 *
 * @param designAbstraction The type of Abstraction that is to be added.
 * @param abstractionDetails A tuple, which takes in 3 strings. which contains the details about the Abstraction.
 */
void DesignAbstractionsInterface::addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails) {
    DesignAbstraction* da = DesignAbstractionsFactory::createDesignAbstraction(designAbstraction, abstractionDetails);
    DesignAbstractionDatabase* db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(da);

    db->addToDatabase(da);
}

void DesignAbstractionsInterface::addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails) {
    if (designAbstraction == "USES" || designAbstraction == "MODIFIES") {
        throw InvalidAPICallException((designAbstraction + " Cannot Be Accessed Via This API").data());
    }
    string underline = "_";
    this->addDesignAbstraction(designAbstraction,
                               make_tuple(underline, get<0>(abstractionDetails), get<1>(abstractionDetails)));
}

/**
 * Returns a Result Object, containing the Design Abstraction Details. These can
 * be accessed by the Result methods to be acted upon further.
 *
 * @param abstractionType Type of Abstraction to obtain.
 * @param query Query contains the Design Entity type being abstracted along with the Entity Name.
 * @return Result object with the result or "None" if the result does not exist.
 */
Result DesignAbstractionsInterface::getDesignAbstraction(string abstractionType, tuple<string, string> query) {
    DesignAbstractionDatabase* db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase(abstractionType,
                                                                                              get<0>(query));
    Result queryResult = db->getFromDatabase(get<1>(query));

    return queryResult;
}

Result DesignAbstractionsInterface::getDesignAbstraction(string abstractionType, string query) {
    if (abstractionType == "USES" || abstractionType == "MODIFIES") {
        throw InvalidAPICallException((abstractionType + " Cannot Be Accessed Via This API").data());
    }

    return this->getDesignAbstraction(abstractionType, make_tuple("_", query));
}

vector<Result> DesignAbstractionsInterface::getAllDesignAbstractions(string designAbstractionType, string entityTypeBeingAbstracted) {
    DesignAbstractionDatabase* db =
            DesignAbstractionsDatabaseFactory::getAbstractionDatabase(designAbstractionType,
                                                                      entityTypeBeingAbstracted);
    return db->getAllFromDatabase();
}

unordered_map<string, unordered_set<string>>
DesignAbstractionsInterface::getAllVariablesCapturedByDesignAbstraction(string designAbstractionType, string entityTypeBeingAbstracted) {
    DesignAbstractionDatabase* db =
            DesignAbstractionsDatabaseFactory::getAbstractionDatabase(designAbstractionType,
                                                                      entityTypeBeingAbstracted);
    return db->getAllVariablesCaptured();
}
