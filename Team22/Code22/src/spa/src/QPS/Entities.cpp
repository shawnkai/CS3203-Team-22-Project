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

StmtEntity::StmtEntity(int lineNumber) : DesignEntity("STATEMENT") {
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity() : DesignEntity("STATEMENT") {}


int StmtEntity::getLine() {
    return this->lineNumber;
}

string StmtEntity::toString() {
    return to_string(this->getLine());
}

ReadEntity::ReadEntity(int lineNumber) : StmtEntity("READ", lineNumber) {}
ReadEntity::ReadEntity() : StmtEntity("READ") {}
PrintEntity::PrintEntity(int lineNumber) : StmtEntity("PRINT", lineNumber) {}
PrintEntity::PrintEntity() : StmtEntity("PRINT") {}
AssignEntity::AssignEntity(int lineNumber) : StmtEntity("ASSIGN", lineNumber) {}
AssignEntity::AssignEntity() : StmtEntity("ASSIGN") {}
CallEntity::CallEntity(int lineNumber) : StmtEntity("CALL", lineNumber) {}
CallEntity::CallEntity() : StmtEntity("CALL") {}
WhileEntity::WhileEntity(int lineNumber) : StmtEntity("WHILE", lineNumber) {}
WhileEntity::WhileEntity() : StmtEntity("WHILE") {}
IfEntity::IfEntity(int lineNumber) : StmtEntity("IF", lineNumber) {}
IfEntity::IfEntity() : StmtEntity("IF") {}


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

ProcedureEntity::ProcedureEntity(string synonym) : NamedEntity("PROCEDURE", std::move(synonym)) {}
VariableEntity::VariableEntity(string synonym) : NamedEntity("VARIABLE", std::move(synonym)) {}
ConstantEntity::ConstantEntity(string synonym) : NamedEntity("CONSTANT", std::move(synonym)) {}

