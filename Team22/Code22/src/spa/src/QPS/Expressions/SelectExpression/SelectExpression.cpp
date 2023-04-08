//
// Created by Tanishq Sharma on 5/3/23.
//

#include "SelectExpression.h"

regex SelectExpression::SYNATTRREGEX = regex(R"(([\w]+)(?:\.((?:\w|#)+))?)");

SelectExpression::SelectExpression(vector<DesignEntity *> entities, vector<string> attributes, vector<Expression *> conditions) : Expression(entities) {
    this->conditions = std::move(conditions);

    for (int i = 0; i < entities.size(); ++i) {
        DesignEntity *entity = entities[i];
        string attribute = attributes[i];
        if (!attribute.empty() && !entity->checkAttr(attribute)) {
            throw SemanticException();
        }
        this->synAttrs.push_back(attribute);
    }
}

string SelectExpression::toString() {
    string res = "Select ";

    if (entities.empty()) {
        res += "BOOLEAN";
    } else if (entities.size() == 1) {
        res += entities[0]->toString();
        if (!synAttrs[0].empty()) {
            res += "." + synAttrs[0];
        }
    } else {
        res += "<";
        for (int i = 0; i < entities.size(); ++i) {
            DesignEntity *entity = entities[i];
            string synAttr = synAttrs[i];
            res += entity->toString();
            if (!synAttr.empty())
                res += "." + synAttr;
            if (i < entities.size() - 1) {
                res += ", ";
            }
        }
        res += ">";
    }

    if (!conditions.empty()) {
        res += " such that";
        for (Expression *e: this->conditions) {
            res += " " + e->toString();
        }
    }
    return res;
}

pair<vector<DesignEntity *>, vector<string>> SelectExpression::extractSynonymsAndAttributes(string query, SynonymTable synonymTable) {
    vector<DesignEntity *> entities = {};
    vector<string> attrs = {};

    smatch sm;
    regex_search(query, sm, Expression::RETURNVALUEREGEX);

    if (!sm.str(1).empty()) {
        if (isBooleanType(sm.str(1), synonymTable)) {
            return make_pair(entities, attrs);
        } else {
            //is a synonym(attr)
            pair<DesignEntity *, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm.str(1), synonymTable);
            entities.push_back(synonymAndAttribute.first);
            attrs.push_back(synonymAndAttribute.second);
        }
    } else if (!sm.str(2).empty()) {
        //is a tuple
        smatch sm2;
        string tuple_string = sm.str(2);
        string::const_iterator searchStart(tuple_string.begin());

        while (regex_search(searchStart, tuple_string.cend(), sm2, SYNATTRREGEX)) {
            pair<DesignEntity *, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm2.str(0), synonymTable);
            entities.push_back(synonymAndAttribute.first);
            attrs.push_back(synonymAndAttribute.second);
            searchStart = sm2.suffix().first;
        }
    } else {
        throw SyntacticException();
    }

    return make_pair(entities, attrs);
}

bool SelectExpression::isBooleanType(string synAttr, SynonymTable synonymTable) {
    return synAttr == "BOOLEAN" && !synonymTable.exists("BOOLEAN");
}

pair<DesignEntity *, string> SelectExpression::extractSynonymAndAttribute(string synAttr, SynonymTable synonymTable) {
    if (!regex_match(synAttr, SYNATTRREGEX)) {
        throw SyntacticException();
    }

    smatch sm;
    regex_search(synAttr, sm, SYNATTRREGEX);

    DesignEntity *entity = synonymTable.get(sm.str(1), "select");
    string attr = sm.str(2);

    if (!attr.empty() && !entity->checkAttr(attr)) {
        throw SemanticException();
    }

    return make_pair(entity, attr);
}

ResultTable *SelectExpression::evaluate(PKB pkb) {
    vector<string> columns;
    vector<ResultTable *> selectEntityTables;
    for (int i = 0; i < this->entities.size(); i++) {
        map<string, vector<string>> finalResults;
        DesignEntity *entity = this->entities[i];
        string synAttr = this->synAttrs[i];
        auto results = pkb.getAllDesignEntity(entity->getType());
        vector<string> answer;
        for (auto res: results) {
            if (entity->getType() == "VARIABLE" || entity->getType() == "PROCEDURE" || entity->getType() == "CONSTANT") {
                answer.push_back(res.getQueryEntityName());
            } else {
                for (const string &a: res.getQueryResult()) {
                    if (!Utilities::checkIfPresent(answer, a)) {
                        answer.push_back(a);
                    }
                }
            }
        }

        finalResults.insert({entity->toString(), answer});

        if (!synAttr.empty()) {
            finalResults.insert({entity->toString() + "." + synAttr, entity->getAttrVal(synAttr, pkb)->getValues("withCond")});
            columns.push_back(entity->toString() + "." + synAttr);
        } else {
            columns.push_back(entity->toString());
        }
        selectEntityTables.push_back(new ResultTable(finalResults));
    }
    auto *selectResult = new ResultTable({});
    if (!selectEntityTables.empty()) {
        selectResult = ResultTable::intersection(selectEntityTables);
    }
    if (this->conditions.empty()) {
        return selectResult;
    } else {
        vector<ResultTable *> allResults;
        for (Expression *exp: this->conditions) {
            ResultTable *temp = exp->evaluate(pkb);
            allResults.push_back(temp);
        }
        if (!this->entities.empty()) {
            allResults.push_back(selectResult);
            ResultTable *t = ResultTable::intersection(allResults)->getColumns(columns);
            return t;
        }

        ResultTable *finalTable = ResultTable::intersection(allResults);
        if (this->entities.empty()) {
            if (finalTable->getSize() > 0) {
                return new BooleanTrueTable();
            } else {
                return new BooleanFalseTable();
            }
        } else {
            return finalTable;
        }
    }
}
