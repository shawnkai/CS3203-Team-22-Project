#include<stdio.h>

#include "Parser.h"
#include "Utilities.h"
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

QueryParser::QueryParser() {}

SelectExpression* QueryParser::parse(string query) {
    vector<Expression*> conditions;

    query = sanitiseQuery(query);
    if (this->isDeclaration(query) || query.empty()) {
		this->extractDeclarations(query);
		return new SelectExpression({}, conditions);
	} else if (this->isValidQuery(query)) {
		smatch sm;
		regex_search(query, sm, RETURNVALUEREGEX);
		
		DesignEntity *arg = this->synonymTable.get(sm.str(1), "select");

		if (this->containsModifiesExpression(query)) {
            vector<ModifiesExpression*> modifiesConditions = this->extractModifiesExpression(query);
			for (ModifiesExpression *e : modifiesConditions) {
                conditions.push_back(e);
            }
		}

        if (this->containsUsesExpression(query)) {
            vector<UsesExpression*> usesConditions = this->extractUsesExpression(query);
            for (UsesExpression *e : usesConditions) {
                conditions.push_back(e);
            }
		}

        if (this->containsPatternExpression(query)) {
            vector<PatternExpression*> patternConditions = this ->extractPatternExpression(query);
            for (PatternExpression *e : patternConditions) {
                conditions.push_back(e);
            }
        }

        if (this->containsFollowsExpression(query)) {
            vector<FollowsExpression*> followsConditions = this->extractFollowsExpression(query);
            for (FollowsExpression *e : followsConditions) {
                conditions.push_back(e);
            }
        }

        if (this->containsFollowsStarExpression(query)) {
            vector<FollowsStarExpression*> followsStarConditions = this ->extractFollowsStarExpression(query);
            for (FollowsStarExpression *e : followsStarConditions) {
                conditions.push_back(e);
            }
        }

        if (this->containsParentExpression(query)) {
            vector<ParentExpression*> parentConditions = this->extractParentExpression(query);
            for (ParentExpression *e : parentConditions) {
                conditions.push_back(e);
            }
        }

        if (this->containsParentStarExpression(query)) {
            vector<ParentStarExpression*> parentStarConditions = this ->extractParentStarExpression(query);
            for (ParentStarExpression *e : parentStarConditions) {
                conditions.push_back(e);
            }
        }

        return new SelectExpression({arg}, conditions);
	} else {
        throw SyntacticException();
    }
}

string QueryParser::sanitiseQuery(const string& query) {
    string result_query = regex_replace(query, std::regex("^ +| +$|( ) +"), "$1");
    result_query = regex_replace(result_query, std::regex(R"(\s+(?=(?:(?:[^"]*"){2})*[^"]*"[^"]*$))"), "$1");
    return result_query;
}

bool QueryParser::isValidQuery(const string& query) {
    return regex_match(query, QUERYVALIDATIONREGEX);
}

bool QueryParser::isDeclaration(const string& query) {
	return regex_match(query, ISDECLARATIONREGEX);
}

bool QueryParser::containsModifiesExpression(string query) {
	return distance(sregex_iterator(query.begin(), query.end(), CONTAINSMODIFIESREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsUsesExpression(string query) {
	return distance(sregex_iterator(query.begin(), query.end(), CONTAINSUSESREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsFollowsExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsFollowsStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSSTARREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsParentExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSPARENTREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsParentStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSPARENTSTARREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsPatternExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSPATTERNREGEX), std::sregex_iterator()) > 0;
}

vector<ModifiesExpression*> QueryParser::extractModifiesExpression(const string& query) {
	smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ModifiesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, MODIFIESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            NamedEntity *a2;

            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else {
                a2 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg2, "named"));
            }
            expressions.push_back(new ModifiesSExpression(a1, a2));
        } else {

            NamedEntity *a1;

            if (arg1 == "_") {
                throw SemanticException();
            } else if (arg1.find('\"') != string::npos) {
                a1 = new NamedEntity("ident", arg1);
            } else if (!Utilities::isAlphanumericString(arg1)) {
                throw SyntacticException();
            } else {
                a1 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg1, "named"));
            }

            NamedEntity *a2;

            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isAlphanumericString(arg2)) {
                throw SyntacticException();
            } else {
                a2 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg2, "named"));
            }

            if (a1->getType() == "VARIABLE" || a1->getType() == "CONSTANT") {
                throw SemanticException();
            }

            expressions.push_back(new ModifiesPExpression(a1,  a2));
        }
        searchStart = sm.suffix().first;
	}
    return expressions;
}

vector<UsesExpression*> QueryParser::extractUsesExpression(const string& query) {
	smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<UsesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, USESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);
        ::printf("Arguments: %s, %s\n", arg1.c_str(), arg2.c_str());
        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isAlphanumericString(arg2)) {
                ::printf("THROWN ERROR\n");
                throw SyntacticException();
            } else {
                a2 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg2, "named"));
            }
            expressions.push_back(new UsesSExpression(a1, a2));
        } else {
            NamedEntity *a1;

            if (arg1 == "_") {
                ::printf("THROWN ERROR\n");
                throw SemanticException();
            } else if (arg1.find('\"') != string::npos) {
                a1 = new NamedEntity("ident", arg1);
            } else if (!Utilities::isAlphanumericString(arg1)) {
                throw SyntacticException();
            } else {
                a1 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg1, "named"));
            }

            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isAlphanumericString(arg2)) {
                throw SyntacticException();
            } else {
                a2 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg2, "named"));
            }

            if (a1->getType() == "VARIABLE" || a1->getType() == "CONSTANT") {
                ::printf("THROWN ERROR\n");
                throw SemanticException();
            }

            expressions.push_back(new UsesPExpression(a1,  a2));
        }
        searchStart = sm.suffix().first;
    }

    return expressions;
}

vector<PatternExpression*> QueryParser::extractPatternExpression(const string& query) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<PatternExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, PATTERNREGEX)) {
        string arg3 = sm.str(3);
        arg3 = Utilities::removeAllOccurrences(arg3, ' ');

        if (arg3.size() == 1 && arg3[0] != '_') {
            throw SyntacticException();
        } else if (arg3.size() != 1) {
            if (arg3.find('\"') == string::npos) {
                throw SyntacticException();
            } else if (arg3[0] == '_' && arg3[arg3.size() - 1] != '_') {
                throw SyntacticException();
            } else if (arg3[0] != '_' && (arg3[0] != '\"' || arg3[arg3.size() - 1] != '\"')) {
                throw SyntacticException();
            } else if (arg3[0] == '_' && (arg3[1] != '\"' || arg3[arg3.size() - 2] != '\"')) {
                throw SyntacticException();
            } else if (!regex_match(arg3, regex(R"(_?\"[A-Za-z0-9+\-*/%)(]+\"_?)"))) {
                throw SyntacticException();
            }
        }

        string arg1 = sm.str(1);

        string arg2 = sm.str(2);

        NamedEntity* a2;
        if (arg2.find('\"') != string::npos) {
            a2 = new NamedEntity("ident", arg2);
        } else if (arg2 == "_") {
            a2 = new WildCardEntity();
        } else {
            a2 = dynamic_cast<NamedEntity*>(this->synonymTable.get(arg2, "named"));
            if (a2->getType() != "VARIABLE") {
                throw SemanticException();
            }
        }

        auto *a1 = dynamic_cast<StmtEntity*>(this->synonymTable.get(arg1, "stmt"));
        string prefixPattern = Utilities::infixToPrefix(Utilities::removeAllOccurrences(arg3, '"'));
        if (a1->getType() != "ASSIGNMENT") {
            throw SemanticException();
        }
        expressions.push_back(new PatternExpression(a1,  a2, prefixPattern));

        searchStart = sm.suffix().first;
    }

    return expressions;
}

tuple<StmtEntity*, StmtEntity*> QueryParser::generateStmtEntityPair(string arg1, string arg2) {
    StmtEntity *a1;
    StmtEntity *a2;

    if (Utilities::isNumber(arg1)) {
        a1 = new StmtEntity(stoi(arg1));
    } else if (arg1 == "_") {
        a1 = new StmtEntity();
    } else {
        a1 = dynamic_cast<StmtEntity*>(this->synonymTable.get(arg1, "stmt"));
        if (a1->getType() == "VARIABLE" || a1->getType() == "PROCEDURE" || a1->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    if (Utilities::isNumber(arg2)) {
        a2 = new StmtEntity(stoi(arg2));
    } else if (arg2 == "_") {
        a2 = new StmtEntity();
    } else {
        a2 = dynamic_cast<StmtEntity*>(this->synonymTable.get(arg2, "stmt"));
        if (a2->getType() == "VARIABLE" || a2->getType() == "PROCEDURE" || a2->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    return std::make_tuple(a1, a2);
}

vector<FollowsExpression*> QueryParser::extractFollowsExpression(const string& query) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<FollowsExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, FOLLOWSREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2));

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new FollowsExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<FollowsStarExpression*> QueryParser::extractFollowsStarExpression(const string& query) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<FollowsStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, FOLLOWSSTARREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2));

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new FollowsStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<ParentExpression*> QueryParser::extractParentExpression(const string& query) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ParentExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, PARENTREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2));

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new ParentExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<ParentStarExpression*> QueryParser::extractParentStarExpression(const string& query) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ParentStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, PARENTSTARREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2));

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new ParentStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

void QueryParser::extractDeclarations(string query) {
	smatch sm;
	auto begin = sregex_iterator(query.begin(), query.end(), EXTRACTDECLARATIONREGEX);
    auto end = sregex_iterator();

	for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;                                                 
        string type = match.str(2);
        string name =  match.str(3);

        unsigned long pos = 0;
        string delimiter = ", ";
        if (name.find(delimiter) != std::string::npos) {
            while ((pos = name.find(delimiter)) != std::string::npos) {
                string subname = name.substr(0, pos);
                if (subname.empty()) {
                    break;
                }
                this->synonymTable.add(type, subname);
                name.erase(0, pos + delimiter.length());
            }
        }
        if (!name.empty()) {
            this->synonymTable.add(type, name);
        }
	}
}

SynonymTable QueryParser::getSynonymTable() {
    return this->synonymTable;
}

