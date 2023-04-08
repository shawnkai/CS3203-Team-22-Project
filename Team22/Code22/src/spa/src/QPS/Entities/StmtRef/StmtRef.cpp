//
// Created by Tanishq Sharma on 8/4/23.
//

#include "StmtRef.h"

StmtRef::StmtRef(string type) : DesignEntity(std::move(type)) {}

WildcardStmtRef::WildcardStmtRef() : StmtRef("STATEMENT") {}

string WildcardStmtRef::toString() const {
    return "_";
}

StmtEntity::StmtEntity(int lineNumber) : StmtRef("STMTENTITY") {
    if (lineNumber <= 0) {
        throw SemanticException();
    }
    this->lineNumber = lineNumber;
}

StmtEntity::StmtEntity(int lineNumber, bool ignoreLineCheck) : StmtRef("STMTENTITY") {
    if (!ignoreLineCheck and lineNumber <= 0) {
        throw SemanticException();
    }
    this->lineNumber = lineNumber;
}

int StmtEntity::getLine() const {
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

string SynonymStmtEntity::toString() const {
    return this->synonym;
}

vector<string> StmtRef::validAttrs = {"stmt#"};

string StmtEntity::toString() const {
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

ResultTable* StmtRef::getAttrVal(string attr, PKB pkb) {
    if (attr == "stmt#") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        vector<string> column;
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                column.push_back(l);
            }
        }
        return new ResultTable({{"withCond", column}, {this->toString(), column}});
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* StmtEntity::getAttrVal(string attr, PKB pkb) {
    return new ResultTable({{"withCond", {to_string(this->lineNumber)}}});
}

ResultTable* CallEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "procName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        unordered_map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return new ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* ReadEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        unordered_map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return new ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* PrintEntity::getAttrVal(string attr, PKB pkb) {
    if (attr == "varName") {
        vector<Result> results = pkb.getAllDesignEntity(this->getType());
        unordered_map<string, vector<string>> data = {{this->toString(), {}}, {"withCond", {}}};
        for (Result r: results) {
            for (string l : r.getQueryResult()) {
                data[this->toString()].push_back(l);
                data["withCond"].push_back(r.getQueryEntityName());
            }
        }
        return new ResultTable(data);
    } else if (attr == "stmt#"){
        return StmtRef::getAttrVal(attr, pkb);
    } else {
        ::printf("incorrect validation\n");
        ::printf("invalid attr : %s", attr.c_str());
        throw SyntacticException();
    }
}

ResultTable* WhileEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable* IfEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable* AssignEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

ResultTable* SynonymStmtEntity::getAttrVal(string attr, PKB pkb) {
    return StmtRef::getAttrVal(attr, pkb);
}

bool StmtRef::checkAttr(string attr) {
    return Utilities::checkIfPresent(StmtRef::validAttrs, attr);
}

bool SynonymStmtEntity::checkAttr(string attr) {
    return Utilities::checkIfPresent(SynonymStmtEntity::validAttrs, attr);
}

bool StmtEntity::checkAttr(string attr) {
    return attr == "";
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