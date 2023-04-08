//
// Created by Atin Sakkeer Hussain on 31/01/2023.
//

#ifndef INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
#define INC_22S2_CP_SPA_TEAM_22_ENTITIES_H

#include "PKB/PKB.h"
#include "QPS/Evaluator/ResultTable.h"
#include <Utilities.h>
#include <list>
#include <string>
#include <utility>

using namespace std;

class DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    string entityType;

public:
    explicit DesignEntity(string entityType);

    DesignEntity();

    string getType();

    virtual string toString() {
        return "";
    }

    virtual ResultTable *getAttrVal(string attr, PKB pkb) {
        return new ResultTable({});
    };

    virtual bool checkAttr(string attr) {
        return false;
    }
};


class StmtRef : public DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    explicit StmtRef(string type);

public:
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class SynonymStmtEntity : public StmtRef {
private:
    static vector<string> validAttrs;

protected:
    string synonym;
    SynonymStmtEntity(string type, string synonym);

public:
    string toString() override;
    explicit SynonymStmtEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WildcardStmtRef : public StmtRef {
public:
    WildcardStmtRef();
    string toString() override;
};

class StmtEntity : public StmtRef {
private:
    int lineNumber;

public:
    int getLine();
    string toString() override;
    explicit StmtEntity(int lineNumber);
};

class ReadEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ReadEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class PrintEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit PrintEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class AssignEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit AssignEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class CallEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit CallEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WhileEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit WhileEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class IfEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit IfEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};


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
    NamedEntity(const string &type, string synonym);

    string getSynonym();

    string toString() override;

    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ProcedureEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ProcedureEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class VariableEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit VariableEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ConstantEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ConstantEntity(string synonym);
    ResultTable *getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WildcardNamedEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit WildcardNamedEntity();
    bool checkAttr(string attr) override;
};

#endif//INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
