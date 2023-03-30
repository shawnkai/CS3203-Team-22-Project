//
// Created by Tanishq Sharma on 5/3/23.
//

#include "SelectExpression.h"

regex SelectExpression::SYNATTRREGEX = regex(R"(([\w]+)(?:\.((?:\w|#)+))?)");

SelectExpression::SelectExpression(vector<DesignEntity*> entities, vector<string> attributes, vector<Expression*> conditions) : Expression(entities){
    this->conditions = std::move(conditions);

    for (int i = 0; i < entities.size(); ++i) {
        DesignEntity* entity = entities[i];
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
            DesignEntity* entity = entities[i];
            string synAttr = synAttrs[i];
            res += entity->toString();
            if (!synAttr.empty())
                res += "." + synAttr;
            if (i < entities.size() - 1) {
                res+=", ";
            }
        }
        res += ">";
    }

    if (!conditions.empty()) {
        res += " such that";
        for (Expression* e : this->conditions) {
            res += " " + e->toString();
        }
    }
    return res;
}

pair<vector<DesignEntity*>, vector<string>> SelectExpression::extractSynonymsAndAttributes(string query, SynonymTable synonymTable) {
    vector<DesignEntity*> entities = {};
    vector<string> attrs = {};

    smatch sm;
    regex_search(query, sm, Expression::RETURNVALUEREGEX);

    if (!sm.str(1).empty()) {
        if (sm.str(1) == "BOOLEAN") {
            return make_pair(entities, attrs);
        } else {
            //is a synonym(attr)
            pair<DesignEntity*, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm.str(1), synonymTable);
            entities.push_back(synonymAndAttribute.first);
            attrs.push_back(synonymAndAttribute.second);
        }
    } else if (!sm.str(2).empty()) {
        //is a tuple
        smatch sm2;
        string tuple_string = sm.str(2);
        string::const_iterator searchStart(tuple_string.begin());

        while (regex_search(searchStart, tuple_string.cend(), sm2, SYNATTRREGEX)) {
            pair<DesignEntity*, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm2.str(0), synonymTable);
            entities.push_back(synonymAndAttribute.first);
            attrs.push_back(synonymAndAttribute.second);
            searchStart = sm2.suffix().first;
            ::printf("%s, %s\n", synonymAndAttribute.first->toString().c_str(), synonymAndAttribute.second.c_str());
        }
    } else {
        throw SyntacticException();
    }

    return make_pair(entities, attrs);
}

pair<DesignEntity*, string> SelectExpression::extractSynonymAndAttribute(string synAttr, SynonymTable synonymTable) {
    if (!regex_match(synAttr, SYNATTRREGEX) or synAttr=="BOOLEAN") {
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


ResultTable SelectExpression::evaluate(PKB pkb) {
    map<string, vector<string>> finalResults;
    vector<string> columns;
    for (int i = 0; i < this->entities.size(); i++) {
        DesignEntity *entity = this->entities[i];
        string synAttr = this->synAttrs[i];
        auto results = pkb.getAllDesignEntity(entity->getType());
        vector<string> answer;
        for (auto res : results) {
            if (entity->getType() == "VARIABLE" || entity->getType() == "PROCEDURE" || entity->getType() == "CONSTANT") {
                answer.push_back(res.getQueryEntityName());
            } else {
                for (const string& a : res.getQueryResult()) {
                    if (!Utilities::checkIfPresent(answer, a)) {
                        answer.push_back(a);
                    }
                }
            }
        }

        finalResults.insert({entity->toString(), answer});

        if (!synAttr.empty()) {
            finalResults.insert({entity->toString() + "." + synAttr, entity->getAttrVal(synAttr, pkb).getValues("withCond")});
            columns.push_back(entity->toString() + "." + synAttr);
        } else {
            columns.push_back(entity->toString());
        }

    }
    ResultTable SelectResult = ResultTable(finalResults);

    if (this->conditions.empty()) {
        return SelectResult;
    } else {
        vector<ResultTable> allResults;
        for (Expression *exp : this->conditions) {
            ResultTable temp = exp->evaluate(pkb);
            allResults.push_back(temp);
        }
        allResults.push_back(SelectResult);
        return ResultTable::intersection(allResults).getColumns(columns);
    }
}
