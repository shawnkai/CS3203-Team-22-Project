//
// Created by Tanishq Sharma on 4/3/23.
//

#ifndef SPA_SYNONYMTABLE_H
#define SPA_SYNONYMTABLE_H

#include "QPS/Exceptions/Exceptions.h"
#include "QPS/Entities/StmtRef/StmtRef.h"
#include "QPS/Entities/NamedEntity/NamedEntity.h"
#include <map>
#include <vector>


/**
 * A class representing a synonym table that maps entity names to their corresponding DesignEntity objects.
 */
class SynonymTable {
private:
    unordered_map<string, DesignEntity*> table; /**< An unordered map storing entity names and their corresponding DesignEntity objects. */

public:
    /**
     * @brief Returns a vector of tuples containing pairs of entity names and their types in the synonym table.
     *
     * @return A vector of tuples containing pairs of entity names and their types in the synonym table.
     */
    vector<tuple<string, string>> getSimpleSynonymTable();

    /**
     * @brief Checks if an entity with the given name exists in the synonym table.
     *
     * @param name The name of the entity to check for existence.
     * @return True if an entity with the given name exists in the synonym table, false otherwise.
     */
    bool exists(string name);

    /**
     * @brief Adds a synonym entity to the synonym table.
     *
     * @param type The type of the synonym entity to add.
     * @param name The name of the synonym entity to add.
     *
     * @throws SyntacticException if the entity already exists in the table.
     */
    void add(string type, const string& name);

    /**
     * @brief Checks if the current synonym table is equivalent to the expected synonym table.
     *
     * @param expectedTable An unordered map representing the expected synonym table.
     *
     * @return True if the current synonym table is equivalent to the expected synonym table, false otherwise.
     */
    bool isEquivalentTo(const unordered_map<string, string>& expectedTable);

    /**
     * @brief Retrieves a synonym entity from the table with the specified name and type.
     *
     * @param name The name of the synonym entity to retrieve.
     * @param desiredType The desired type of the synonym entity to retrieve.
     *
     * @throws SemanticException if the entity does not exist in the table.
     *
     * @return A pointer to the desired synonym entity.
     */
    DesignEntity *get(const string& name, const string& desiredType);
};

#endif //SPA_SYNONYMTABLE_H
