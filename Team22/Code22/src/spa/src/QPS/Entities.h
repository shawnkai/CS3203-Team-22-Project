//
// Created by Atin Sakkeer Hussain on 31/01/2023.
//

#ifndef INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
#define INC_22S2_CP_SPA_TEAM_22_ENTITIES_H

#include <string>
#include <utility>

using namespace std;

class DesignEntity {

protected:
    string entityType;

public:
    explicit DesignEntity(string entityType);

    DesignEntity();

    string getType();

    virtual string toString() {
        return "";
    }
};

class StmtEntity : public DesignEntity {
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
};

class ReadEntity : public StmtEntity {
public:
    explicit ReadEntity(int lineNumber);
    explicit ReadEntity(string synonym);
    ReadEntity();
};

class PrintEntity : public StmtEntity {
public:
    explicit PrintEntity(int lineNumber);
    explicit PrintEntity(string synonym);
    PrintEntity();
};

class AssignEntity : public StmtEntity {
public:
    explicit AssignEntity(int lineNumber);
    explicit AssignEntity(string synonym);
    AssignEntity();
};

class CallEntity : public StmtEntity {
public:
    explicit CallEntity(int lineNumber);
    explicit CallEntity(string synonym);
    CallEntity();
};

class WhileEntity : public StmtEntity {
public:
    explicit WhileEntity(int lineNumber);
    explicit WhileEntity(string synonym);
    WhileEntity();
};

class IfEntity : public StmtEntity {
public:
    explicit IfEntity(int lineNumber);
    explicit IfEntity(string synonym);
    IfEntity();
};


class NamedEntity : public DesignEntity {
protected:
    string synonym;
public:
    NamedEntity(const string& type, string synonym);

    string getSynonym();

    string toString() override;
};

class ProcedureEntity : public NamedEntity {
public:
    explicit ProcedureEntity(string synonym);
};

class VariableEntity : public NamedEntity {
public:
    explicit VariableEntity(string synonym);
};

class ConstantEntity : public NamedEntity {
public:
    explicit ConstantEntity(string synonym);
};

class WildCardEntity : public NamedEntity {
public:
    explicit WildCardEntity();
};

#endif //INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
