//
// Created by Tanishq Sharma on 4/3/23.
//

#include "SynonymTable.h"
#include <stdexcept>

void SynonymTable::add(string type, const string& name) {
    if (this->table.count(name)) {
        throw SyntacticException();
    }
    if (type == "stmt") {
        this->table[name] = new SynonymStmtEntity(name);
    } else if (type == "read") {
        this->table[name] = new ReadEntity(name);
    } else if (type == "print") {
        this->table[name] = new PrintEntity(name);
    } else if (type == "call") {
        this->table[name] = new CallEntity(name);
    } else if (type == "while") {
        this->table[name] = new WhileEntity(name);
    } else if (type == "if") {
        this->table[name] = new IfEntity(name);
    } else if (type == "assign") {
        this->table[name] = new AssignEntity(name);
    } else if (type == "variable") {
        this->table[name] = new VariableEntity(name);
    } else if (type == "constant") {
        this->table[name] = new ConstantEntity(name);
    } else if (type == "procedure") {
        this->table[name] = new ProcedureEntity(name);
    }
}

DesignEntity *SynonymTable::get(const string& name, const string& desiredType) {
    if (!table.count(name)) {
        throw SemanticException();
    }

    DesignEntity *entity = table.at(name);

    if (desiredType == "stmt") {
        return new SynonymStmtEntity(name);
    } else if (desiredType == "named") {
        return new NamedEntity(entity->getType(), name);
    } else if (desiredType == "select"){
        return entity;
    } else {
        string errorMsg = "unknown type: " + desiredType;
        throw std::runtime_error(errorMsg);
    }

}

vector<tuple<string, string>> SynonymTable::getSimpleSynonymTable() {
    vector<tuple<string, string>> result;
    for (tuple<string, DesignEntity*> t : this->table) {
        result.emplace_back(std::get<0>(t), std::get<1>(t)->getType());
    }
    return result;
}

bool SynonymTable::isEquivalentTo(const map<string, string>& expectedTable) {
    vector<tuple<string, string>> result = this->getSimpleSynonymTable();
    map<string, string> actualTable;
    for (auto & i : result) {
        actualTable[std::get<0>(i)] = std::get<1>(i);
    }

    return actualTable == expectedTable;
}
