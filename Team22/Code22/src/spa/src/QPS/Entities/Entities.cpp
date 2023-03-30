//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#include "Entities.h"
#include "QPS/Exceptions/Exceptions.h"
#include "Utilities.h"

// Design Entity
DesignEntity::DesignEntity(string entityType) {
    this->entityType = std::move(entityType);
};

string DesignEntity::getType() {
    return this->entityType;
}

DesignEntity::DesignEntity() {}

StmtRef::StmtRef(string type) : DesignEntity(std::move(type)) {}

WildcardStmtRef::WildcardStmtRef() : StmtRef("STATEMENT") {}

string WildcardStmtRef::toString() {
    return "_";
}

StmtEntity::StmtEntity(int lineNumber) : StmtRef("STMTENTITY") {
    if (lineNumber <= 0) {
        throw SemanticException();
    }
    this->lineNumber = lineNumber;
}

int StmtEntity::getLine() {
    return this->lineNumber;
}

SynonymStmtEntity::SynonymStmtEntity(string type, string synonym) : StmtRef(std::move(type)) {
    if (!Utilities::isValidVariableName(synonym)) {
        throw SyntacticException();
    }
    this->synonym = std::move(synonym);
}

SynonymStmtEntity::SynonymStmtEntity(string synonym) : StmtRef("STATEMENT") {
    if (!Utilities::isValidVariableName(synonym)) {
        throw SyntacticException();
    }
    this->synonym = std::move(synonym);
}

string SynonymStmtEntity::toString() {
    return this->synonym;
}

vector<string> StmtRef::validAttrs = {"stmt#"};

string StmtEntity::toString() {
    return to_string(this->getLine());
}

ReadEntity::ReadEntity(string synonym) : SynonymStmtEntity("READ", std::move(synonym)) {}
vector<string> ReadEntity::validAttrs = {"varName", "stmt#"};

PrintEntity::PrintEntity(string synonym) : SynonymStmtEntity("PRINT", std::move(synonym)) {}
vector<string>  PrintEntity::validAttrs = {"varName", "stmt#"};

AssignEntity::AssignEntity(string synonym) : SynonymStmtEntity("ASSIGNMENT", std::move(synonym)) {}
vector<string>  AssignEntity::validAttrs = {"stmt#"};

CallEntity::CallEntity(string synonym) : SynonymStmtEntity("CALL", std::move(synonym)) {}
vector<string>  CallEntity::validAttrs = {"procName", "stmt#"};

WhileEntity::WhileEntity(string synonym) : SynonymStmtEntity("WHILE", std::move(synonym)) {}
vector<string>  WhileEntity::validAttrs = {"stmt#"};

IfEntity::IfEntity(string synonym) : SynonymStmtEntity("IF", std::move(synonym)) {}
vector<string>  IfEntity::validAttrs = {"stmt#"};

vector<string> SynonymStmtEntity::validAttrs = {"stmt#"};

// Named Entities and its children
NamedEntity::NamedEntity(const string& type, string synonym) : DesignEntity(type) {
    string synonym_removed = Utilities::removeAllOccurrences(synonym, '\"');
    if (!Utilities::isValidVariableName(synonym_removed) && synonym != "_" && !Utilities::isNumber(synonym_removed)) {
        throw SyntacticException();
    }
    if (type == "ident" && (synonym[0] != '\"' || synonym[synonym.size() - 1] != '\"')) {
        ::printf("ERROR SYN: %s\n", synonym.c_str());
        throw SyntacticException();
    }
    this->synonym = synonym_removed;
}

string NamedEntity::getSynonym() {
    return this->synonym;
}

string NamedEntity::toString() {
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

ResultTable StmtRef::getAttrVal(string attr, PKB pkb) {
    if (attr == "stmt#") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                column.push_back(l);
            }
        }
        return ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable ProcedureEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "procName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable CallEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "procName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable VariableEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable ReadEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable PrintEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable ConstantEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "value") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        column.reserve(results.size());
        for (Result r: results) {
            column.push_back(r.getQueryEntityName());
        }
        return ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable NamedEntity::getAttrVal(string attr, PKB pkb) {
    if (this->getType() == "ident" || this->getType() == "int") {
        return ResultTable({{"withCond", {Utilities::removeAllOccurrences(this->toString(), '\"')}}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid type : %s", this->getType().c_str());
        throw SyntacticException();
    }
}

ResultTable WhileEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable IfEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable AssignEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable SynonymStmtEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

bool NamedEntity::checkAttr(string attr) {
    return false;
}

bool StmtRef::checkAttr(string attr) {
    return Utilities::checkIfPresent(StmtRef::validAttrs, attr);
}

bool SynonymStmtEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(SynonymStmtEntity::validAttrs, attr);
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

bool AssignEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(AssignEntity::validAttrs, attr);
}

bool CallEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(CallEntity::validAttrs, attr);
}

bool PrintEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(PrintEntity::validAttrs, attr);
}

bool IfEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(IfEntity::validAttrs, attr);
}

bool WhileEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(WhileEntity::validAttrs, attr);
}

bool ReadEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(ReadEntity::validAttrs, attr);
}

bool WildcardNamedEntity::checkAttr(string attr) {
    return false;
}