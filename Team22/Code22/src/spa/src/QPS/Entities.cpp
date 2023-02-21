//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#include "QPS/Entities.h"
#include "QPS/Exceptions.h"
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
PrintEntity::PrintEntity(int lineNumber) : StmtEntity("PRINT", lineNumber) {}
PrintEntity::PrintEntity() : StmtEntity("PRINT") {}
PrintEntity::PrintEntity(string synonym) : StmtEntity("PRINT", std::move(synonym)) {}
AssignEntity::AssignEntity(int lineNumber) : StmtEntity("ASSIGNMENT", lineNumber) {}
AssignEntity::AssignEntity() : StmtEntity("ASSIGNMENT") {}
AssignEntity::AssignEntity(string synonym) : StmtEntity("ASSIGNMENT", std::move(synonym)) {}
CallEntity::CallEntity(int lineNumber) : StmtEntity("CALL", lineNumber) {}
CallEntity::CallEntity() : StmtEntity("CALL") {}
CallEntity::CallEntity(string synonym) : StmtEntity("CALL", std::move(synonym)) {}
WhileEntity::WhileEntity(int lineNumber) : StmtEntity("WHILE", lineNumber) {}
WhileEntity::WhileEntity() : StmtEntity("WHILE") {}
WhileEntity::WhileEntity(string synonym) : StmtEntity("WHILE", std::move(synonym)) {}
IfEntity::IfEntity(int lineNumber) : StmtEntity("IF", lineNumber) {}
IfEntity::IfEntity() : StmtEntity("IF") {}
IfEntity::IfEntity(string synonym) : StmtEntity("IF", std::move(synonym)) {}


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

ProcedureEntity::ProcedureEntity(string synonym) : NamedEntity("PROCEDURE", std::move(synonym)) {}
VariableEntity::VariableEntity(string synonym) : NamedEntity("VARIABLE", std::move(synonym)) {}
ConstantEntity::ConstantEntity(string synonym) : NamedEntity("CONSTANT", std::move(synonym)) {}

WildCardEntity::WildCardEntity() : NamedEntity("WILDCARD", "_") {}