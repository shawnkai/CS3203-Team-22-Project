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

    string getType();

    virtual string toString() {
        return "";
    }

    virtual ResultTable getAttrVal(string attr, PKB pkb) {
        return ResultTable({});
    };

    virtual bool checkAttr(string attr) {
        return false;
    }
};


class StmtEntity : public DesignEntity {
    /**
     * StmtEntity Class is the super class for ReadEntity, PrintEntity, AssignEntity, CallEntity, IfEntity and WhileEntity
     * it can be initialized with the specific type and its line number or the specific type and the synonym used in declaration
     */
private:
    static vector<string> validAttrs;

protected:
    int lineNumber = -1;
    string synonym = "-1";

public:
    StmtEntity(string type,  int lineNumber);
    StmtEntity(string type, string synonym);
    StmtEntity(string type);
    StmtEntity(int lineNumber);
    StmtEntity();

    int getLine();

    string toString() override;
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;

};

class ReadEntity : public StmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ReadEntity(int lineNumber);
    explicit ReadEntity(string synonym);
    ReadEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class PrintEntity : public StmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit PrintEntity(int lineNumber);
    explicit PrintEntity(string synonym);
    PrintEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class AssignEntity : public StmtEntity {
private:
    static vector<string> validAttrs;
public:
    explicit AssignEntity(int lineNumber);
    explicit AssignEntity(string synonym);
    AssignEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class CallEntity : public StmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit CallEntity(int lineNumber);
    explicit CallEntity(string synonym);
    CallEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WhileEntity : public StmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit WhileEntity(int lineNumber);
    explicit WhileEntity(string synonym);
    WhileEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class IfEntity : public StmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit IfEntity(int lineNumber);
    explicit IfEntity(string synonym);
    IfEntity();
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};


class NamedEntity : public DesignEntity {
    /**
     * NamedEntity class is the super class for ProcedureEntity, VariableEntity, ConstantEntity and WildCardEntity
     * This class stores the specific type of the NamedEntity and also its synonym
     */
private:
    static vector<string> validAttrs;

protected:
    string synonym;
public:
    NamedEntity(const string& type, string synonym);

    string getSynonym();

    string toString() override;

    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ProcedureEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ProcedureEntity(string synonym);
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class VariableEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit VariableEntity(string synonym);
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class ConstantEntity : public NamedEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ConstantEntity(string synonym);
    ResultTable getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WildCardEntity : public NamedEntity {
private:
    static vector<string> validAttrs;
public:
    explicit WildCardEntity();
    bool checkAttr(string attr) override;
};

#endif //INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
