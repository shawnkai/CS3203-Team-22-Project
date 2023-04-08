//
// Created by Tanishq Sharma on 8/4/23.
//

#ifndef SPA_STMTREF_H
#define SPA_STMTREF_H

#include "QPS/Entities/DesignEntities.h"

/**
 * A class that represent all StmtRef entities.
 */
class StmtRef : public DesignEntity {

private:
    static vector<string> validAttrs;

protected:
    explicit StmtRef(string type);

public:
    /**
     * Returns a ResultTable with the specified attribute value(s) for the StmtRef.
     *
     * @param attr The attribute for which to retrieve value(s).
     * @param pkb The Program Knowledge Base.
     *
     * @return ResultTable* A ResultTable containing the value(s) of the specified attribute for the StmtRef.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the specified attribute is valid for StmtRef.
     *
     * @param attr The attribute to check.
     * @return true If the attribute is valid for StmtRef.
     * @return false If the attribute is not valid for StmtRef.
     */
    bool checkAttr(string attr) override;

};

/**
 * A class that represent all synonym statement types.
 */
class SynonymStmtEntity : public StmtRef {
private:
    static vector<string> validAttrs;

protected:
    string synonym;

    /**
     * Constructs a SynonymStmtEntity object with the specified type and synonym.
     *
     * @param type A string indicating the type of the SynonymStmtEntity object.
     * @param synonym A string indicating the synonym of the SynonymStmtEntity object.
     */
    SynonymStmtEntity(string type, string synonym);
public:
    string toString() const override;

    /**
      * Constructs a SynonymStmtEntity object with the specified synonym.
      *
      * @param synonym A string indicating the synonym of the SynonymStmtEntity object.
      */
    explicit SynonymStmtEntity(string synonym);

    /**
     * Returns the attribute value of the given attribute for this SynonymStmtEntity object.
     *
     * @param attr A string indicating the attribute to be retrieved.
     * @param pkb A PKB object to be used for attribute retrieval.
     *
     * @return ResultTable* A pointer to the ResultTable containing the requested attribute value(s).
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the given attribute is valid for this SynonymStmtEntity object.
     *
     * @param attr A string indicating the attribute to be checked.
     *
     * @return true If the attribute is valid.
     * @return false If the attribute is not valid.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing a Wildcard statement refrence.
 */
class WildcardStmtRef: public StmtRef {
public:
    /**
     * Constructs a WildcardStmtRef object.
     */
    WildcardStmtRef();

    /**
     * Returns a string representation of this WildcardStmtRef object.
     *
     * @return string A string representation of this WildcardStmtRef object.
     */
    string toString() const override;
};

/**
 * A class representing a StmtEntity.
 */
class StmtEntity: public StmtRef {
private:
    int lineNumber;
public:
    /**
     * Returns the line number of this StmtEntity object.
     *
     * @return int The line number of this StmtEntity object.
     */
    int getLine() const;
    string toString() const override;

    /**
     * Constructs a StmtEntity object.
     *
     * @param lineNumber The line number of the statement.
     */
    explicit StmtEntity(int lineNumber);

    /**
     * Constructs a StmtEntity object, while ignoring line check.
     *
     * @param lineNumber The line number of the statement.
     * @param lineNumber The line number of the statement.
     */
    explicit StmtEntity(int lineNumber, bool ignoreLineCheck);

    /**
     * Returns the attribute value of the given attribute for this StmtEntity object.
     *
     * @param attr A string indicating the attribute to be retrieved.
     * @param pkb A PKB object to be used for attribute retrieval.
     *
     * @return ResultTable* A pointer to the ResultTable containing the requested attribute value(s).
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the given attribute is valid for this StmtEntity object.
     *
     * @param attr A string indicating the attribute to be checked.
     *
     * @return true If the attribute is valid.
     * @return false If the attribute is not valid.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing a Read statement entity.
 * Inherits from SynonymStmtEntity.
 */
class ReadEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    /**
     * Constructs a ReadEntity object.
     *
     * @param synonym The synonym of the statement.
     */
    explicit ReadEntity(string synonym);

    /**
     * Returns the attribute value(s) of the statement.
     *
     * @param attr The attribute to retrieve.
     * @param pkb A pointer to the PKB.
     *
     * @return A pointer to a ResultTable object containing the attribute value(s) of the statement.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the given attribute is a valid attribute for the statement.
     *
     * @param attr The attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing a Print statement entity.
 * Inherits from SynonymStmtEntity.
 */
class PrintEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    /**
     * Constructs a PrintEntity object.
     *
     * @param synonym The synonym of the statement.
     */
    explicit PrintEntity(string synonym);

    /**
     * Returns the attribute value(s) of the statement.
     *
     * @param attr The attribute to retrieve.
     * @param pkb A pointer to the PKB.
     *
     * @return A pointer to a ResultTable object containing the attribute value(s) of the statement.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the given attribute is a valid attribute for the statement.
     *
     * @param attr The attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing an Assign statement entity.
 * Inherits from SynonymStmtEntity.
 */
class AssignEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;
public:
    /**
     * Constructs an AssignEntity object.
     * @param synonym The synonym of the statement.
     */
    explicit AssignEntity(string synonym);

    /**
     * Returns the attribute value(s) of the statement.
     *
     * @param attr The attribute to retrieve.
     * @param pkb A pointer to the PKB.
     *
     * @return A pointer to a ResultTable object containing the attribute value(s) of the statement.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks if the given attribute is a valid attribute for the statement.
     *
     * @param attr The attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing an Call statement entity.
 * Inherits from SynonymStmtEntity.
 */
class CallEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    /**
     * Constructor for CallEntity class.
     *
     * @param synonym the synonym of the call statement.
     */
    explicit CallEntity(string synonym);

    /**
     * Returns the values of the attribute specified for the call statement.
     *
     * @param attr the attribute to get values for.
     * @param pkb the PKB object to query.
     *
     * @return a pointer to the table of results for the specified attribute.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks whether the specified attribute is valid for the call statement.
     *
     * @param attr the attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing a While statement entity.
 * Inherits from SynonymStmtEntity.
 */
class WhileEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    /**
     * Constructor for WhileEntity class.
     *
     * @param synonym the synonym of the while statement.
     */
    explicit WhileEntity(string synonym);


    /**
     * Returns the values of the attribute specified for the while statement.
     *
     * @param attr the attribute to get values for.
     * @param pkb the PKB object to query.
     *
     * @return a pointer to the table of results for the specified attribute.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks whether the specified attribute is valid for the while statement.
     *
     * @param attr the attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * A class representing an If statement entity.
 * Inherits from SynonymStmtEntity.
 */
class IfEntity : public SynonymStmtEntity {
private:
    static vector<string> validAttrs;

public:
    /**
     * Constructor for IfEntity class.
     *
     * @param synonym the synonym of the if statement.
     */
    explicit IfEntity(string synonym);

    /**
     * Returns the values of the attribute specified for the if statement.
     *
     * @param attr the attribute to get values for.
     * @param pkb the PKB object to query.
     *
     * @return a pointer to the table of results for the specified attribute.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Checks whether the specified attribute is valid for the if statement.
     *
     * @param attr the attribute to check.
     *
     * @return true if the attribute is valid, false otherwise.
     */
    bool checkAttr(string attr) override;
};

#endif //SPA_STMTREF_H
