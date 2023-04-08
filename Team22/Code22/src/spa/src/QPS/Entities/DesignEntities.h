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

class DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    string entityType;

public:
    explicit DesignEntity(string entityType);

    DesignEntity();

    string getType() const;

    virtual string toString() const {
        return "";
    }

    virtual ResultTable* getAttrVal(string attr, PKB pkb) {
        return new ResultTable({});
    };

    virtual bool checkAttr(string attr) {
        return false;
    }
};

#endif //INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
