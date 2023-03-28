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

    if (entities.size() == 1) {
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
        //is a synonym
        pair<DesignEntity*, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm.str(1), synonymTable);
        entities.push_back(synonymAndAttribute.first);
        attrs.push_back(synonymAndAttribute.second);
    } else if (!sm.str(2).empty()) {
        //is a tuple
        smatch sm2;
        string tuple_string = sm.str(2);
        string::const_iterator searchStart(tuple_string.begin());

        while (regex_search(searchStart, tuple_string.cend(), sm2, SYNATTRREGEX)) {
            pair<DesignEntity*, string> synonymAndAttribute = SelectExpression::extractSynonymAndAttribute(sm2.str(0), synonymTable);
            entities.push_back(synonymAndAttribute.first);
            attrs.push_back(synonymAndAttribute.second);
        }
    } else {
        throw SyntacticException();
    }

    return {entities, attrs};
}

pair<DesignEntity*, string> SelectExpression::extractSynonymAndAttribute(string synAttr, SynonymTable synonymTable) {
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

    return {entity, attr};
}


ResultTable SelectExpression::evaluate(PKB pkb) {
//    if (this->conditions.empty()) {
//        auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
//        vector<string> answer;
//        for (auto res : results) {
//            if (this->entities[0]->getType() == "VARIABLE" || this->entities[0]->getType() == "PROCEDURE" || this->entities[0]->getType() == "CONSTANT") {
//                answer.push_back(res.getQueryEntityName());
//            } else {
//                for (string a : res.getQueryResult()) {
//                    if (!Utilities::checkIfPresent(answer, a)) {
//                        answer.push_back(a);
//                    }
//                }
//            }
//        }
//        if (!this->synAttr.empty()) {
//            return this->entities[0]->getAttrVal(this->synAttr, pkb);
//        }
//        return ResultTable({make_pair(this->entities[0]->toString(), answer)});
//    } else {
//        vector<ResultTable> all_results;
//        for (Expression *exp : this->conditions) {
//            ResultTable temp = exp->evaluate(pkb);
//            all_results.push_back(temp);
//        }
//        ResultTable table = ResultTable::intersection(all_results);
//        vector<string> tableColumns = table.getColumnNames();
//        if (!Utilities::checkIfPresent(tableColumns, this->entities[0]->toString())) {
//            if (table.getSize() == 0) {
//                if (!this->synAttr.empty()) {
//                    return ResultTable({{this->entities[0]->toString() + "." + this->synAttr, {}}});
//                }
//                return ResultTable({{this->entities[0]->toString(), {}}});
//            }
//            auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
//            vector<string> answer;
//            for (auto res : results) {
//                if (this->entities[0]->getType() == "VARIABLE" || this->entities[0]->getType() == "PROCEDURE" || this->entities[0]->getType() == "CONSTANT") {
//                    answer.push_back(res.getQueryEntityName());
//                } else {
//                    for (const string& a : res.getQueryResult()) {
//                        if (!Utilities::checkIfPresent(answer, a)) {
//                            answer.push_back(a);
//                        }
//                    }
//                }
//            }
//            if (!this->synAttr.empty()) {
//                return ResultTable({make_pair(this->entities[0]->toString(), answer)})
//                .intersection(this->entities[0]->getAttrVal(this->synAttr, pkb));
//            }
//            return ResultTable({make_pair(this->entities[0]->toString(), answer)});
//        }
//        if (!this->synAttr.empty()) {
//            ResultTable temp = table.getColumn(this->entities[0]->toString()).intersection(this->entities[0]->getAttrVal(this->synAttr, pkb));
//            temp.renameColumn("withCond", this->entities[0]->toString() + "." + this->synAttr);
//            return temp.getColumn(this->entities[0]->toString() + "." + this->synAttr);
//        }
//        return table.getColumn(this->entities[0]->toString());
//    }
    return {};
}

