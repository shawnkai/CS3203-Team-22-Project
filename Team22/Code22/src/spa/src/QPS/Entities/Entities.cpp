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

//Stmt Entity and its children
StmtEntity::StmtEntity(string type, int lineNumber) : DesignEntity(std::move(type)) {
    if (lineNumber <= 0) {
        throw SemanticException();
    }
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity(string type, string synonym) : DesignEntity(std::move(type)) {
    if (!Utilities::isAlphanumericString(synonym)) {
        throw SyntacticException();
    }
    this->synonym = std::move(synonym);
}

StmtEntity::StmtEntity(string type) : DesignEntity(std::move(type)) {}

StmtEntity::StmtEntity(int lineNumber) : DesignEntity("STATEMENT") {
    if (lineNumber <= 0) {
        throw SemanticException();
    }
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity() : DesignEntity("STATEMENT") {}

vector<string> StmtEntity::validAttrs = {"stmt#"};

int StmtEntity::getLine() {
    return this->lineNumber;
}

string StmtEntity::toString() {
    if (this->getLine() == -1 && this->synonym == "-1") {
        return "_";
    } else if (this->getLine() == -1) {
        return this->synonym;
    } else {
        return to_string(this->getLine());
    }
}

ReadEntity::ReadEntity(int lineNumber) : StmtEntity("READ", lineNumber) {}
ReadEntity::ReadEntity() : StmtEntity("READ") {}
ReadEntity::ReadEntity(string synonym) : StmtEntity("READ", std::move(synonym)) {}
vector<string> ReadEntity::validAttrs = {"varName", "stmt#"};

PrintEntity::PrintEntity(int lineNumber) : StmtEntity("PRINT", lineNumber) {}
PrintEntity::PrintEntity() : StmtEntity("PRINT") {}
PrintEntity::PrintEntity(string synonym) : StmtEntity("PRINT", std::move(synonym)) {}
vector<string>  PrintEntity::validAttrs = {"varName", "stmt#"};

AssignEntity::AssignEntity(int lineNumber) : StmtEntity("ASSIGNMENT", lineNumber) {}
AssignEntity::AssignEntity() : StmtEntity("ASSIGNMENT") {}
AssignEntity::AssignEntity(string synonym) : StmtEntity("ASSIGNMENT", std::move(synonym)) {}
vector<string>  AssignEntity::validAttrs = {"stmt#"};

CallEntity::CallEntity(int lineNumber) : StmtEntity("CALL", lineNumber) {}
CallEntity::CallEntity() : StmtEntity("CALL") {}
CallEntity::CallEntity(string synonym) : StmtEntity("CALL", std::move(synonym)) {}
vector<string>  CallEntity::validAttrs = {"procName", "stmt#"};

WhileEntity::WhileEntity(int lineNumber) : StmtEntity("WHILE", lineNumber) {}
WhileEntity::WhileEntity() : StmtEntity("WHILE") {}
WhileEntity::WhileEntity(string synonym) : StmtEntity("WHILE", std::move(synonym)) {}
vector<string>  WhileEntity::validAttrs = {"stmt#"};

IfEntity::IfEntity(int lineNumber) : StmtEntity("IF", lineNumber) {}
IfEntity::IfEntity() : StmtEntity("IF") {}
IfEntity::IfEntity(string synonym) : StmtEntity("IF", std::move(synonym)) {}
vector<string>  IfEntity::validAttrs = {"stmt#"};


// Named Entities and its children
NamedEntity::NamedEntity(const string& type, string synonym) : DesignEntity(type) {
    string synonym_removed = Utilities::removeAllOccurrences(synonym, '\"');
    if (!Utilities::isAlphanumericString(synonym_removed) && synonym != "_") {
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

WildCardEntity::WildCardEntity() : NamedEntity("WILDCARD", "_") {}

ResultTable StmtEntity::getAttrVal(string attr, PKB pkb) {
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
        return StmtEntity::getAttrVal(attr, pkb);
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
        return StmtEntity::getAttrVal(attr, pkb);
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
        return StmtEntity::getAttrVal(attr, pkb);
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
    return StmtEntity::getAttrVal(attr, pkb);
}

ResultTable IfEntity::getAttrVal(string attr, PKB pkb) {
    return StmtEntity::getAttrVal(attr, pkb);
}

ResultTable AssignEntity::getAttrVal(string attr, PKB pkb) {
    return StmtEntity::getAttrVal(attr, pkb);
}

bool NamedEntity::checkAttr(string attr) {
    return false;
}

bool StmtEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(StmtEntity::validAttrs, attr);
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

bool WildCardEntity::checkAttr(string attr) {
    return false;
}