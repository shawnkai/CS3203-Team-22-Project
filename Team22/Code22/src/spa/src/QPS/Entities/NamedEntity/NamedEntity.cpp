//
// Created by Tanishq Sharma on 8/4/23.
//

#include "NamedEntity.h"

NamedEntity::NamedEntity(const string& type, string synonym) : DesignEntity(type) {
    string synonym_removed = Utilities::removeAllOccurrences(synonym, '\"');

    if (!Utilities::isValidVariableName(synonym_removed) && synonym != "_") {
        throw SyntacticException();
    }
    if (type == "ident" && (synonym[0] != '\"' || synonym[synonym.size() - 1] != '\"')) {
        ::printf("ERROR SYN: %s\n", synonym.c_str());
        throw SyntacticException();
    }
    this->synonym = synonym_removed;
}

string NamedEntity::getSynonym() const {
    return this->synonym;
}

string NamedEntity::toString() const {
    if (this->getType() == "ident") {
        return "\"" + this->getSynonym() + "\"";
    }
    return this->getSynonym();
}

ProcedureEntity::ProcedureEntity(string synonym) : NamedEntity("PROCEDURE", std::move(synonym)) {};
vector<string>  ProcedureEntity::validAttrs = {"procName"};

VariableEntity::VariableEntity(string synonym) : NamedEntity("VARIABLE", std::move(synonym)) {}
vector<string>  VariableEntity::validAttrs = {"varName"};

ConstantEntity::ConstantEntity(string synonym) : NamedEntity("CONSTANT", std::move(synonym)) {}
vector<string>  ConstantEntity::validAttrs = {"value"};

WildcardNamedEntity::WildcardNamedEntity() : NamedEntity("WILDCARD", "_") {}

ResultTable* ProcedureEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "procName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return new ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* VariableEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return new ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* ConstantEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "value") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return new ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* NamedEntity::getAttrVal(string attr, PKB pkb) {
    if (this->getType() == "ident" || this->getType() == "int") {
        return new ResultTable({{"withCond", {Utilities::removeAllOccurrences(this->toString(), '\"')}}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid type : %s", this->getType().c_str());
        throw SyntacticException();
    }
}

bool NamedEntity::checkAttr(string attr) {
    return false;
}

bool ProcedureEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(ProcedureEntity::validAttrs, attr);
}

bool VariableEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(VariableEntity::validAttrs, attr);
}

bool ConstantEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(ConstantEntity::validAttrs, attr);
}

bool WildcardNamedEntity::checkAttr(string attr) {
    return false;
}