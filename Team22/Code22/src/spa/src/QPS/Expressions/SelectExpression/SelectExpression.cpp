//
// Created by Tanishq Sharma on 5/3/23.
//

#include "SelectExpression.h"

SelectExpression::SelectExpression(vector<DesignEntity*> entities, vector<Expression*> conditions) : Expression(std::move(entities)){
    this->conditions = std::move(conditions);
}

string SelectExpression::toString() {
    string res = "Select " + this->entities[0]->toString();

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
        return ResultTable({make_pair(this->entities[0]->toString(), answer)});
    } else {
        vector<ResultTable> all_results;
        for (Expression *exp : this->conditions) {
            all_results.push_back(exp->evaluate(pkb));
        }
        ResultTable table = ResultTable::intersection(all_results);
        vector<string> tableColumns = table.getColumnNames();
        if (!Utilities::checkIfPresent(tableColumns, this->entities[0]->toString())) {
            if (table.getSize() == 0) {
                return ResultTable({{this->entities[0]->toString(), {}}});
            }
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
            return ResultTable({make_pair(this->entities[0]->toString(), answer)});
        }
        return table.getColumn(this->entities[0]->toString());
    }
}

