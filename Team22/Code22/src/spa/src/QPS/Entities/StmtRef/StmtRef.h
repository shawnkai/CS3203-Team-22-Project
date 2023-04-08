//
// Created by Tanishq Sharma on 8/4/23.
//

#ifndef SPA_STMTREF_H
#define SPA_STMTREF_H

#include "QPS/Entities/DesignEntities.h"

class StmtRef : public DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    explicit StmtRef(string type);

public:
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;

};

class SynonymStmtEntity : public StmtRef {
private:
    static vector<string> validAttrs;

protected:
    string synonym;
    SynonymStmtEntity(string type, string synonym);
public:
    string toString() const override;
    explicit SynonymStmtEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WildcardStmtRef: public StmtRef {
public:
    WildcardStmtRef();
    string toString() const override;
};

class StmtEntity: public StmtRef {
private:
    int lineNumber;
public:
    int getLine() const;
    string toString() const override;
    explicit StmtEntity(int lineNumber);
};

class ReadEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit ReadEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class PrintEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit PrintEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class AssignEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;
public:
    explicit AssignEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class CallEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit CallEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class WhileEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit WhileEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

class IfEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    explicit IfEntity(string synonym);
    ResultTable* getAttrVal(string attr, PKB pkb) override;
    bool checkAttr(string attr) override;
};

#endif //SPA_STMTREF_H
