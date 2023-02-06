//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#include "QPS/Entities.h"

#include <utility>

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
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity(string type) : DesignEntity(std::move(type)) {}

StmtEntity::StmtEntity(int lineNumber) : DesignEntity("statement") {
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity() : DesignEntity("statement") {}


int StmtEntity::getLine() {
    return this->lineNumber;
}

string StmtEntity::toString() {
    return to_string(this->getLine());
}

ReadEntity::ReadEntity(int lineNumber) : StmtEntity("read", lineNumber) {}
ReadEntity::ReadEntity() : StmtEntity("read") {}
PrintEntity::PrintEntity(int lineNumber) : StmtEntity("print", lineNumber) {}
PrintEntity::PrintEntity() : StmtEntity("print") {}
AssignEntity::AssignEntity(int lineNumber) : StmtEntity("assign", lineNumber) {}
AssignEntity::AssignEntity() : StmtEntity("assign") {}
CallEntity::CallEntity(int lineNumber) : StmtEntity("call", lineNumber) {}
CallEntity::CallEntity() : StmtEntity("call") {}
WhileEntity::WhileEntity(int lineNumber) : StmtEntity("while", lineNumber) {}
WhileEntity::WhileEntity() : StmtEntity("while") {}
IfEntity::IfEntity(int lineNumber) : StmtEntity("if", lineNumber) {}
IfEntity::IfEntity() : StmtEntity("if") {}


// Named Entities and its children
NamedEntity::NamedEntity(string type, string synonym) : DesignEntity(std::move(type)) {
    this->synonym = std::move(synonym);
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

ProcedureEntity::ProcedureEntity(string synonym) : NamedEntity("procedure", std::move(synonym)) {}
VariableEntity::VariableEntity(string synonym) : NamedEntity("variable", std::move(synonym)) {}
ConstantEntity::ConstantEntity(string synonym) : NamedEntity("constant", std::move(synonym)) {}

