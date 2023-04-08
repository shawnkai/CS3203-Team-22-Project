//
// Created by Tanishq Sharma on 8/4/23.
//

#ifndef SPA_NAMEDENTITY_H
#define SPA_NAMEDENTITY_H

#include "QPS/Entities/DesignEntities.h"

using namespace std;

class NamedEntity : public DesignEntity {
    /**
     * NamedEntity class is the super class for ProcedureEntity, VariableEntity, ConstantEntity and WildcardNamedEntity
     * This class stores the specific type of the NamedEntity and also its synonym
     */
private:
    static vector<string> validAttrs;

protected:
    string synonym;
public:
    NamedEntity(const string& type, string synonym);

    string getSynonym() const;

    string toString() const override;

    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ProcedureEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ProcedureEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class VariableEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit VariableEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ConstantEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ConstantEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WildcardNamedEntity : public NamedEntity {
private:
    static vector<string> validAttrs;
public:
    explicit WildcardNamedEntity();
    bool checkAttr(string attr) override;
};



#endif //SPA_NAMEDENTITY_H
