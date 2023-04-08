//
// Created by Tanishq Sharma on 8/4/23.
//

#ifndef SPA_NAMEDENTITY_H
#define SPA_NAMEDENTITY_H

#include "QPS/Entities/DesignEntities.h"
#include <vector>

using namespace std;

/**
 * The NamedEntity class is the superclass for ProcedureEntity, VariableEntity, ConstantEntity, and
 * WildcardNamedEntity. It stores the specific type of the NamedEntity and its synonym.
 */
class NamedEntity : public DesignEntity {
private:
    static vector<string> validAttrs; ///< Vector of valid attributes for NamedEntity

protected:
    string synonym; ///< Synonym of the NamedEntity

public:
    /**
     * Constructor for NamedEntity.
     *
     * @param type The type of NamedEntity.
     * @param synonym The synonym of NamedEntity.
     */
    NamedEntity(const string& type, string synonym);

    /**
     * Get the synonym of NamedEntity.
     *
     * @return The synonym of NamedEntity.
     */
    string getSynonym() const;

    /**
     * Convert NamedEntity to string representation.
     *
     * @return The string representation of NamedEntity.
     */
    string toString() const override;

    /**
     * Get attribute value for NamedEntity.
     *
     * @param attr The attribute for which value is to be retrieved.
     * @param pkb The PKB instance.
     *
     * @return Pointer to ResultTable containing the attribute value.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Check if the given attribute is valid for NamedEntity.
     *
     * @param attr The attribute to be checked.
     *
     * @return True if the attribute is valid, False otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * The ProcedureEntity class is a derived class of NamedEntity representing ProcedureEntity in the SPA.
 */
class ProcedureEntity : public NamedEntity {
private:
    static vector<string> validAttrs; ///< Vector of valid attributes for ProcedureEntity

public:
    /**
     * Constructor for ProcedureEntity.
     *
     * @param synonym The synonym of ProcedureEntity.
     */
    explicit ProcedureEntity(string synonym);

    /**
     * Get attribute value for ProcedureEntity.
     *
     * @param attr The attribute for which value is to be retrieved.
     * @param pkb The PKB instance.
     *
     * @return Pointer to ResultTable containing the attribute value.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Check if the given attribute is valid for ProcedureEntity.
     *
     * @param attr The attribute to be checked.
     *
     * @return True if the attribute is valid, False otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * The VariableEntity class is a derived class of NamedEntity representing VariableEntity in the SPA.
 */
class VariableEntity : public NamedEntity {
private:
    static vector<string> validAttrs; ///< Vector of valid attributes for VariableEntity

public:
    /**
     * Constructor for VariableEntity.
     *
     * @param synonym The synonym of VariableEntity.
     */
    explicit VariableEntity(string synonym);

    /**
     * Get attribute value for VariableEntity.
     *
     * @param attr The attribute for which value is to be retrieved.
     * @param pkb The PKB instance.
     *
     * @return Pointer to ResultTable containing the attribute value.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Check if the given attribute is valid for VariableEntity.
     *
     * @param attr The attribute to be checked.
     *
     * @return True if the attribute is valid, False otherwise.
     */
    bool checkAttr(string attr) override;
};

/**

@class ConstantEntity
The ConstantEntity class is a derived class of NamedEntity representing ConstantEntity in the SPA.
*/
class ConstantEntity : public NamedEntity {
private:
    static vector<string> validAttrs; ///< Vector of valid attributes for ConstantEntity
public:
    /**
     * Constructor for ConstantEntity.
     *
     * @param synonym The synonym of ConstantEntity.
     */
    explicit ConstantEntity(string synonym);
    /**
     * Get attribute value for ConstantEntity.
     *
     * @param attr The attribute for which value is to be retrieved.
     * @param pkb The PKB instance.
     *
     * @return Pointer to ResultTable containing the attribute value.
     */
    ResultTable* getAttrVal(string attr, PKB pkb) override;

    /**
     * Check if the given attribute is valid for ConstantEntity.
     *
     * @param attr The attribute to be checked.
     *
     * @return True if the attribute is valid, False otherwise.
     */
    bool checkAttr(string attr) override;
};

/**
 * The WildcardNamedEntity class is a derived class of NamedEntity representing WildcardNamedEntity in the SPA.
*/
class WildcardNamedEntity : public NamedEntity {
private:
    static vector<string> validAttrs; ///< Vector of valid attributes for WildcardNamedEntity

public:
    /**
    * Constructor for WildcardNamedEntity.
    */
    explicit WildcardNamedEntity();

    /**
     * Check if the given attribute is valid for WildcardNamedEntity.
     *
     * @param attr The attribute to be checked.
     *
     * @return True if the attribute is valid, False otherwise.
     */
    bool checkAttr(string attr) override;
};

#endif //SPA_NAMEDENTITY_H