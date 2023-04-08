//
// Created by Atin Sakkeer Hussain on 31/01/2023.
//

#ifndef INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
#define INC_22S2_CP_SPA_TEAM_22_ENTITIES_H

#include <string>
#include <Utilities.h>
#include <list>
#include <utility>
#include "QPS/Evaluator/ResultTable.h"
#include "QPS/Exceptions/Exceptions.h"
#include "PKB/PKB.h"

using namespace std;

/**
 * Class representing Design entities in PQL.
 */
class DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    string entityType;

public:
    /**
     * Creates a DesignEntity object with the given entity type.
     *
     * @param entityType The entity type.
     */
    explicit DesignEntity(string entityType);

    /**
     * Creates a default DesignEntity object with an empty entity type.
     */
    DesignEntity();

    /**
     * Returns the entity type of this DesignEntity object.
     *
     * @return The entity type.
     */
    string getType() const;

    virtual string toString() const {
        return "";
    }

    /**
     * Returns the attribute value of the given attribute for this DesignEntity object.
     *
     * @param attr The attribute name.
     * @param pkb The program knowledge base.
     *
     * @return A ResultTable object representing the attribute value of the given attribute for this DesignEntity object.
     */
    virtual ResultTable* getAttrVal(string attr, PKB pkb) {
        return new ResultTable({});
    };

    /**
     * Checks if the given attribute is valid for this DesignEntity object.
     *
     * @param attr The attribute name.
     *
     * @return True if the given attribute is valid, false otherwise.
     */
    virtual bool checkAttr(string attr) {
        return false;
    }
};

#endif //INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
