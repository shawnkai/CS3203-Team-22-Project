//
// Created by Tanishq Sharma on 5/3/23.
//

#include "SelectExpression.h"

SelectExpression::SelectExpression(DesignEntity* entity, vector<Expression*> conditions, string attribute) : Expression({entity}){
    this->conditions = std::move(conditions);
    if (!attribute.empty() && !entity->checkAttr(attribute)) {
        throw SemanticException();
    }
    this->synAttr = attribute;
}

string SelectExpression::toString() {
    string res = "Select " + this->entities[0]->toString();
    if (!this->synAttr.empty())
        res += "." + this->synAttr;

    if (!conditions.empty()) {
        res += " such that";
        for (Expression* e : this->conditions) {
            res += " " + e->toString();
        }
    }
    return res;
}

ResultTable SelectExpression::evaluate(PKB pkb) {
    if (this->conditions.empty()) {
        auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<string> answer;
        for (auto res : results) {
            if (this->entities[0]->getType() == "VARIABLE" || this->entities[0]->getType() == "PROCEDURE" || this->entities[0]->getType() == "CONSTANT") {
                answer.push_back(res.getQueryEntityName());
            } else {
                for (string a : res.getQueryResult()) {
                    if (!Utilities::checkIfPresent(answer, a)) {
                        answer.push_back(a);
                    }
                }
            }
        }
        if (!this->synAttr.empty()) {
            return this->entities[0]->getAttrVal(this->synAttr, pkb);
        }
        return ResultTable({make_pair(this->entities[0]->toString(), answer)});
    } else {
        vector<ResultTable> all_results;
        ResultTable inter({});
        for (Expression *exp : this->conditions) {
            ResultTable temp = exp->evaluate(pkb);
            all_results.push_back(temp);
        }
        ResultTable table = ResultTable::intersection(all_results);
        vector<string> tableColumns = table.getColumnNames();
        if (!Utilities::checkIfPresent(tableColumns, this->entities[0]->toString())) {
            if (table.getSize() == 0) {
                if (!this->synAttr.empty()) {
                    return ResultTable({{this->entities[0]->toString() + "." + this->synAttr, {}}});
                }
                return ResultTable({{this->entities[0]->toString(), {}}});
            }
            auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
            vector<string> answer;
            for (auto res : results) {
                if (this->entities[0]->getType() == "VARIABLE" || this->entities[0]->getType() == "PROCEDURE" || this->entities[0]->getType() == "CONSTANT") {
                    answer.push_back(res.getQueryEntityName());
                } else {
                    for (const string& a : res.getQueryResult()) {
                        if (!Utilities::checkIfPresent(answer, a)) {
                            answer.push_back(a);
                        }
                    }
                }
            }
            if (!this->synAttr.empty()) {
                return ResultTable({make_pair(this->entities[0]->toString(), answer)})
                .intersection(this->entities[0]->getAttrVal(this->synAttr, pkb));
            }
            return ResultTable({make_pair(this->entities[0]->toString(), answer)});
        }
        if (!this->synAttr.empty()) {
            ResultTable temp = table.getColumn(this->entities[0]->toString()).intersection(this->entities[0]->getAttrVal(this->synAttr, pkb));
            temp.renameColumn("withCond", this->entities[0]->toString() + "." + this->synAttr);
            return temp.getColumn(this->entities[0]->toString() + "." + this->synAttr);
        }
        return table.getColumn(this->entities[0]->toString());
    }
}
