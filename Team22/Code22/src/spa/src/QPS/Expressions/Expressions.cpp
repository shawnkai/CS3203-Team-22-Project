//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "Expressions.h"

#include "PKB/PKB.h"
#include <algorithm>
#include <regex>
#include "Utilities.h"
#include "QPS/Exceptions/Exceptions.h"

// Function Definitions

Expression::Expression(vector<DesignEntity*> entities) {
    this->entities = std::move(entities);
}

vector<DesignEntity*> Expression::getAllEntities() {
    return this->entities;
}

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


ModifiesExpression::ModifiesExpression(NamedEntity *target) : Expression({target}) {
    if (target->getType() != "VARIABLE" && target->getType() != "ident" && target->getType() != "WILDCARD") {
        throw SemanticException();
    }
}


ModifiesSExpression::ModifiesSExpression(StmtEntity *modifier, NamedEntity *target) : ModifiesExpression(target) {
    this->entities.push_back(modifier);
}

string ModifiesSExpression::toString() {
    return "Modifies(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

ModifiesPExpression::ModifiesPExpression(NamedEntity *modifier, NamedEntity *target) : ModifiesExpression(target) {
    this->entities.push_back(modifier);
}

string ModifiesPExpression::toString() {
    return "Modifies(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

UsesExpression::UsesExpression(DesignEntity *target) : Expression({target}) {
    if (target->getType() != "VARIABLE" && target->getType() != "ident" && target->getType() != "WILDCARD") {
        throw SemanticException();
    }
}


UsesSExpression::UsesSExpression(StmtEntity* user, DesignEntity* target) : UsesExpression(target) {
    this->entities.push_back(user);
}

string UsesSExpression::toString() {
    return "Uses(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

UsesPExpression::UsesPExpression(NamedEntity* user, DesignEntity* target) : UsesExpression(target) {
    this->entities.push_back(user);
}

string UsesPExpression::toString() {
    return "Uses(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

FAPSExpression::FAPSExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction) : Expression({s1, s2}) {
    this->pkbAbstraction = pkbAbstraction;
}

FollowsExpression::FollowsExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "FOLLOWS") {}

string FollowsExpression::toString() {
    return "Follows(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

FollowsStarExpression::FollowsStarExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "FOLLOWSSTAR") {}

string FollowsStarExpression::toString() {
    return "Follows*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentExpression::ParentExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "PARENT") {}
string ParentExpression::toString() {
    return "Parent(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentStarExpression::ParentStarExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "PARENTSTAR") {}
string ParentStarExpression::toString() {
    return "Parent*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}


PatternExpression::PatternExpression(DesignEntity *entity, NamedEntity* p1, string p2) : Expression({entity}) {
    this->p1 = p1;
    this->p2 = std::move(p2);
}

ResultTable ModifiesSExpression::evaluate(PKB pkb) {
    vector<Result> vars;
    if (this->entities[0]->getType() == "WILDCARD") {
        auto varResult = pkb.getAllDesignEntity("VARIABLE");
        auto constResult = pkb.getAllDesignEntity("CONSTANT");
        vars.insert(vars.end(), varResult.begin(), varResult.end());
        vars.insert(vars.end(), constResult.begin(), constResult.end());
    } else if (this->entities[0]->getType() == "ident") {
        vars.push_back(pkb.getDesignEntity("VARIABLE", dynamic_cast<NamedEntity*>(this->entities[1])->getSynonym()));
    } else {
        vars = pkb.getAllDesignEntity(this->entities[0]->getType());
    }

    vector<Result> results;
    for (auto var : vars) {
        results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
    }
    vector<string> result;
    for (auto res: results) {
        bool found = false;
        for (const auto& s: res.getQueryResult()) {
            if (s == to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine())) {
                found = true;
                break;
            }
        }
        if (found) {
            result.push_back(res.getQueryEntityName());
        }
    }
    return ResultTable({{this->entities[0]->toString(), result}});
}

ResultTable ModifiesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        Result res = pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), varName));
        if (!res.getQueryResult().empty()) {
            vector<string> ans = res.getQueryResult();
            sort(ans.begin(), ans.end());
            return ResultTable({{this->entities[1]->toString(), ans}});
        } else {
            return ResultTable({{this->entities[1]->toString(), {}}});
        }
    } else {
        bool isFirstWildCard = this->entities[1]->getType() == "WILDCARD";

        vector<Result> vars;

        if (this->entities[0]->getType() == "WILDCARD") {
            auto varResult = pkb.getAllDesignEntity("VARIABLE");
            auto constResult = pkb.getAllDesignEntity("CONSTANT");
            vars.insert(vars.end(), varResult.begin(), varResult.end());
            vars.insert(vars.end(), constResult.begin(), constResult.end());
        } else {
            vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        }

        vector<Result> results;
        for (auto var : vars) {
            if (isFirstWildCard) {
                results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", var.getQueryEntityName())));
            } else {
                results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
            }
        }
        map<string, vector<string>> result = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        int ind = 0;
        for (auto res: results) {
            if ((isFirstWildCard && res.getQueryEntityName() != "none") || res.getQueryEntityType() == "MODIFIES:" + dynamic_cast<NamedEntity*>(this->entities[1])->getType()) {
                for (const auto& x : res.getQueryResult()) {
                    result.find(this->entities[0]->toString())->second.push_back(vars[ind].getQueryEntityName());
                    result.find(this->entities[1]->toString())->second.push_back(x);
                }
            }
            ind += 1;
        }
        return ResultTable(result);
    }
}

ResultTable UsesSExpression::evaluate(PKB pkb) {
    auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
    vector<Result> results;
    for (auto var : vars) {
        results.push_back(pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
    }
    vector<string> result;
    for (auto res : results) {
        bool found = false;
        for (const auto& s : res.getQueryResult()) {
            if (s == to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine())) {
                found = true;
                break;
            }
        }
        if (found) {
            result.push_back(res.getQueryEntityName());
        }
    }
    return ResultTable({{this->entities[0]->toString(), result}});
}

ResultTable UsesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        Result res = pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), varName));
        if (res.getQueryEntityName() != "none" && !res.getQueryResult().empty()) {
            return ResultTable({{this->entities[1]->toString(), res.getQueryResult()}});
        }
        else {
            return {};
        }
    }
    else {
        bool isFirstWildCard = this->entities[1]->getType() == "WILDCARD";

        vector<Result> vars;

        if (this->entities[0]->getType() == "WILDCARD") {
            auto varResult = pkb.getAllDesignEntity("VARIABLE");
            auto constResult = pkb.getAllDesignEntity("CONSTANT");
            vars.insert(vars.end(), varResult.begin(), varResult.end());
            vars.insert(vars.end(), constResult.begin(), constResult.end());
        } else {
            vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        }

        vector<Result> results;
        for (auto var : vars) {
            if (isFirstWildCard) {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair("STATEMENT", var.getQueryEntityName())));
            } else {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
            }
        }
        map<string, vector<string>> result = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        int ind = 0;
        for (auto res : results) {
            if ((isFirstWildCard && res.getQueryEntityName() != "none") || res.getQueryEntityType() == "USES:" + dynamic_cast<NamedEntity*>(this->entities[1])->getType()) {
                for (const auto& x : res.getQueryResult()) {
                    result.find(this->entities[1]->toString())->second.push_back(x);
                    result.find(this->entities[0]->toString())->second.push_back(vars[ind].getQueryEntityName());
                }
            }
            ind += 1;
        }
        if (isFirstWildCard) {
            return ResultTable({{this->entities[0]->toString(), result.find(this->entities[0]->toString())->second}});
        }
        return ResultTable(result);
    }
}

ResultTable FAPSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->toString() == "_" && this->entities[1]->toString() == "_") {
        return ResultTable({{"_", {"-"}}});
    }
    else if (this->entities[0]->toString() == this->entities[1]->toString()) {
        return ResultTable({{this->entities[0]->toString(), {}}});
    } else if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1 && dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());

        vector<string> possibleLines;
        for (Result res : vars2) {
            for (string l : res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        map<string, vector<string>> results = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        vector<pair<string, string>> seen;
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                vector<vector<string>> all_vectors;
                all_vectors.push_back(possibleLines);
                all_vectors.push_back(follows.getQueryResult());
                vector<string> followsSatisfied = Utilities::findIntersection(all_vectors);
                for (const string& r : followsSatisfied) {
                    if (find(seen.begin(), seen.end(), make_pair(line, r)) == seen.cend()) {
                        results.find(this->entities[0]->toString())->second.push_back(line);
                        results.find(this->entities[1]->toString())->second.push_back(r);
                        seen.emplace_back(line, r);
                    }
                }
            }
        }
        return ResultTable(results);
    } else if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1) {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        int nextLineInt = dynamic_cast<StmtEntity*>(this->entities[1])->getLine();
        string nextLine = to_string(nextLineInt);
        vector<string> followedLines;
        for (Result res : vars) {
            for (const string& line : res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                if (Utilities::checkIfPresent(follows.getQueryResult(), nextLine)) {
                    followedLines.push_back(line);
                }
            }
        }
        return ResultTable({{this->entities[0]->toString(), followedLines}});
    } else if (dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
        int prevLineInt = dynamic_cast<StmtEntity*>(this->entities[0])->getLine();
        string prevLine = to_string(prevLineInt);
        Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", prevLine));
        auto vars = pkb.getAllDesignEntity(this->entities[1]->getType());
        vector<string> possibleLines;
        for (Result res : vars) {
            for (string l : res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        for (const string& line : possibleLines) {
            if (Utilities::checkIfPresent(follows.getQueryResult(), line)) {
                followedLines.push_back(line);
            }
        }
        return ResultTable({{this->entities[1]->toString(), followedLines}});
    }
    return {};
}

string PatternExpression::toString() {
    return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", " + this->p2 + ")";
}

ResultTable PatternExpression::evaluate(PKB pkb) {
    string prefix_expr = p2;
    prefix_expr = Utilities::removeAllOccurrences(prefix_expr, '\"');
    prefix_expr = regex_replace(prefix_expr, regex("\\-"), "\\-");
    prefix_expr = regex_replace(prefix_expr, regex("\\+"), "\\+");
    prefix_expr = regex_replace(prefix_expr, regex("\\*"), "\\*");
    prefix_expr = regex_replace(prefix_expr, regex("_"), R"([\w\+\-\*/%]*)");
    regex right_expr (prefix_expr);

    if (p1->getSynonym() == "_" || p1->getType() == "VARIABLE") {
        auto key_values = pkb.getAllRightHandExpressions();
        vector<string> results;
        map<string, vector<string>> altResults = {{this->entities[0]->toString(), {}}, {p1->getSynonym(), {}}};
        for (auto pattern : key_values) {
            for (const auto& lineno_expression : pattern->getAllRightHandExpressions()) {
                if (regex_match(lineno_expression.second, right_expr)) {
                    altResults.find(this->entities[0]->toString())->second.push_back(lineno_expression.first);
                    altResults.find(p1->getSynonym())->second.push_back(pattern->getLeftHandVariableName());
                }
            }
        }
        if (p1->getSynonym() == "_") {
            return ResultTable({make_pair(this->entities[0]->toString(), altResults.find(this->entities[0]->toString())->second)});
        }
        return ResultTable(altResults);
    } else {
        auto key_values = pkb.getAllRightHandExpressionsOfAVariable(p1->getSynonym());
        vector<string> result;
        for (const auto& pair : key_values) {
            if (regex_match(pair.second, right_expr)) {
                result.push_back(pair.first);
            }
        }
        return ResultTable({make_pair(this->entities[0]->toString(), result)});
    }
}