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

    string getType();
};

class StmtEntity : DesignEntity {
protected:
    int lineNumber;
public:
    StmtEntity(string type,  int lineNumber);

    int getLine();
};

class ReadEntity : StmtEntity {
public:
    explicit ReadEntity(int lineNumber);
};

class PrintEntity : StmtEntity {
public:
    explicit PrintEntity(int lineNumber);
};

class AssignEntity : StmtEntity {
public:
    explicit AssignEntity(int lineNumber);
};

class CallEntity : StmtEntity {
public:
    explicit CallEntity(int lineNumber);
};

class WhileEntity : StmtEntity {
public:
    explicit WhileEntity(int lineNumber);
};

class IfEntity : StmtEntity {
public:
    explicit IfEntity(int lineNumber);
};


class NamedEntity : DesignEntity {
protected:
    string synonym;
public:
    NamedEntity(string type, string synonym);

    string getSynonym();
};

class ProcedureEntity : NamedEntity {
public:
    explicit ProcedureEntity(string synonym);
};

class VariableEntity : NamedEntity {
public:
    explicit VariableEntity(string synonym);
};

class ConstantEntity : NamedEntity {
public:
    explicit ConstantEntity(string synonym);
};

#endif //INC_22S2_CP_SPA_TEAM_22_ENTITIES_H
