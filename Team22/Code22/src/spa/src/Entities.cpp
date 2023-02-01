//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#include "Entities.h"

// Design Entity
DesignEntity::DesignEntity(string entityType) {
    this->entityType = std::move(entityType);
};

string DesignEntity::getType() {
    return this->entityType;
}

//Stmt Entity and its children
StmtEntity::StmtEntity(string type, int lineNumber) : DesignEntity(type) {
    this->lineNumber = lineNumber;
}

int StmtEntity::getLine() {
    return this->lineNumber;
}

ReadEntity::ReadEntity(int lineNumber) : StmtEntity("read", lineNumber) {}
PrintEntity::PrintEntity(int lineNumber) : StmtEntity("print", lineNumber) {}
AssignEntity::AssignEntity(int lineNumber) : StmtEntity("assign", lineNumber) {}
CallEntity::CallEntity(int lineNumber) : StmtEntity("call", lineNumber) {}
WhileEntity::WhileEntity(int lineNumber) : StmtEntity("while", lineNumber) {}
IfEntity::IfEntity(int lineNumber) : StmtEntity("if", lineNumber) {}


// Named Entities and its children
NamedEntity::NamedEntity(string type, string synonym) : DesignEntity(type) {
    this->synonym = synonym;
}

string NamedEntity::getSynonym() {
    return this->synonym;
}

ProcedureEntity::ProcedureEntity(string synonym) : NamedEntity("procedure", synonym) {}
VariableEntity::VariableEntity(string synonym) : NamedEntity("variable", synonym) {}
ConstantEntity::ConstantEntity(string synonym) : NamedEntity("constant", synonym) {}
