#include<stdio.h>


#include "PKB/PKB.h"
#include "Parser.h"
#include "Utilities.h"


using namespace std;

QueryParser::QueryParser() {}

SelectExpression* QueryParser::parse(const string& query) {
    regex RETURNVALUEREGEX = regex("Select (\\w+)");

    vector<Expression*> conditions;

	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
		return new SelectExpression({}, conditions);
	} else {
		smatch sm;
		regex_search(query, sm, RETURNVALUEREGEX);
		
		DesignEntity *arg = this->synonymTable[sm.str(1)];

		if (this->containsModifiesExpression(query)) {
            vector<ModifiesExpression*> modifiesConditions = this->extractModifiesExpression(query);
			for (ModifiesExpression *e : modifiesConditions) {
                conditions.push_back(e);
            }
		} else if (this->containsUsesExpression(query)) {
            vector<UsesExpression*> usesConditions = this->extractUsesExpression(query);
            for (UsesExpression *e : usesConditions) {
                conditions.push_back(e);
            }
		} else if (this->containsPatternExpression(query)) {
            vector<PatternExpression*> patternConditions = this ->extractPatternExpression(query);
            for (PatternExpression *e : patternConditions) {
                conditions.push_back(e);
            }
        } else if (this->containsFollowsExpression(query)) {
            vector<FollowsExpression*> followsConditions = this->extractFollowsExpression(query);
            for (FollowsExpression *e : followsConditions) {
                conditions.push_back(e);
            }
        } else if (this->containsFollowsStarExpression(query)) {
            vector<FollowsStarExpression*> followsStarConditions = this ->extractFollowsStarExpression(query);
            for (FollowsStarExpression *e : followsStarConditions) {
                conditions.push_back(e);
            }
        } else if (this->containsParentExpression(query)) {
            vector<ParentExpression*> parentConditions = this->extractParentExpression(query);
            for (ParentExpression *e : parentConditions) {
                conditions.push_back(e);
            }
        } else if (this->containsParentStarExpression(query)) {
            vector<ParentStarExpression*> parentStarConditions = this ->extractParentStarExpression(query);
            for (ParentStarExpression *e : parentStarConditions) {
                conditions.push_back(e);
            }
        }

        return new SelectExpression({arg}, conditions);
	}
}

bool QueryParser::isDeclaration(const string& query) {
	regex ISDECLARATIONREGEX = regex("((^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) ((\\w|, )+))+;");
	return regex_match(query, ISDECLARATIONREGEX);
}

bool QueryParser::containsModifiesExpression(string query) {
	regex CONTAINSMODIFIESREGEX = regex(R"lit(Modifies\s?\("?(\w+)"?, "?(\w+)"?\))lit");
	return distance(sregex_iterator(query.begin(), query.end(), CONTAINSMODIFIESREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsUsesExpression(string query) {
	regex CONTAINSUSESREGEX = regex(R"lit(Uses\s?\("?(\w+)"?, "?(\w+)"?\))lit");
	return distance(sregex_iterator(query.begin(), query.end(), CONTAINSUSESREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsFollowsExpression(string query) {
    regex CONTAINSFOLLOWSREGEX = regex(R"lit(Follows\s?\("?(\w+)"?, "?(\w+)"?\))lit");
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsFollowsStarExpression(string query) {
    regex CONTAINSFOLLOWSSTARREGEX = regex(R"lit(Follows\*\s?\("?(\w+)"?, "?(\w+)"?\))lit");
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSSTARREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsParentExpression(string query) {
    regex CONTAINSFOLLOWSREGEX = regex(R"lit(Parent\s?\("?(\w+)"?, "?(\w+)"?\))lit");
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsParentStarExpression(string query) {
    regex CONTAINSFOLLOWSSTARREGEX = regex(R"lit(Parent\*\s?\("?(\w+)"?, "?(\w+)"?\))lit");
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSFOLLOWSSTARREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsPatternExpression(string query) {
    regex CONTAINSPATTERNREGEX = regex(R"(pattern (\w+)\(((?:_?\"?[\w]+\"?_?)|_)\s*,\s*((?:_?\"?[\w\+\-\*/]+\"?_?)|_)\))");
    return distance(sregex_iterator(query.begin(), query.end(), CONTAINSPATTERNREGEX), std::sregex_iterator()) > 0;
}

vector<ModifiesExpression*> QueryParser::extractModifiesExpression(const string& query) {
	regex MODIFIESREGEX = regex(R"lit(Modifies\s?\(("?\w+"?), ("?\w+"?)\))lit");
	smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ModifiesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, MODIFIESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            auto *a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
            expressions.push_back(new ModifiesSExpression(a1, a2));
        } else {
            NamedEntity *a1;

            if (arg1 == "_") {
                a1 = new WildCardEntity();
            } else if (arg1.find('\"') != string::npos) {
                arg1 = Utilities::removeAllOccurrences(arg1, '\"');
                a1 = new NamedEntity("ident", arg1);
            } else {
                a1 = new NamedEntity(this->synonymTable[arg1]->getType(), arg1);
            }

            NamedEntity *a2;

            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                arg2 = Utilities::removeAllOccurrences(arg2, '\"');
                a2 = new NamedEntity("ident", arg2);
            } else {
                a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
            }

            expressions.push_back(new ModifiesPExpression(a1,  a2));
        }
        searchStart = sm.suffix().first;
	}
    return expressions;
}

vector<UsesExpression*> QueryParser::extractUsesExpression(const string& query) {
	regex USESREGEX = regex(R"lit(Uses\s?\(("?\w+"?), ("?\w+"?)\))lit");
	smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<UsesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, USESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            auto *a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
            expressions.push_back(new UsesSExpression(a1, a2));
        } else {
            NamedEntity *a1;

            if (arg1 == "_") {
                a1 = new WildCardEntity();
            } else if (arg1.find('\"') != string::npos) {
                arg1 = Utilities::removeAllOccurrences(arg1, '\"');
                a1 = new NamedEntity("ident", arg1);
            } else {
                a1 = new NamedEntity(this->synonymTable[arg1]->getType(), arg1);
            }

            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                arg2 = Utilities::removeAllOccurrences(arg2, '\"');
                a2 = new NamedEntity("ident", arg2);
            } else {
                a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
            }
            expressions.push_back(new UsesPExpression(a1,  a2));
        }
        searchStart = sm.suffix().first;
    }

    return expressions;
}

vector<PatternExpression*> QueryParser::extractPatternExpression(const string& query) {
    regex USESPATTERN = regex(R"(pattern (\w+)\(((?:_?\"?[\w]+\"?_?)|_)\s*,\s*((?:_?\"?[\w\+\-\*/]+\"?_?)|_)\))");
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<PatternExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, USESPATTERN)) {
        string arg1 = sm.str(1);

        string arg2 = sm.str(2);

        NamedEntity* a2;
        if (arg2.find('\"') != string::npos) {
            arg2 = Utilities::removeAllOccurrences(arg2, '\"');
            a2 = new NamedEntity("ident", arg2);
        } else if (arg2 == "_") {
            a2 = new WildCardEntity();
        }else {
            a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
        }

        string arg3 = sm.str(3);
        arg3 = Utilities::removeAllOccurrences(arg3, '\"');

        auto *a1 = new NamedEntity(this->synonymTable[arg1]->getType(), arg1);
        string prefixPattern = Utilities::infixToPrefix(Utilities::removeAllOccurrences(arg3, '"'));

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
        a1 = new StmtEntity(-1);
    } else {
        a1 = new StmtEntity(this->synonymTable[arg1]->getType(), arg1);
    }

    if (Utilities::isNumber(arg2)) {
        a2 = new StmtEntity(stoi(arg2));
    } else if (arg2 == "_") {
        a2 = new StmtEntity(-1);
    } else {
        a2 = new StmtEntity(this->synonymTable[arg2]->getType(), arg2);
    }

    return std::make_tuple(a1, a2);
}

vector<FollowsExpression*> QueryParser::extractFollowsExpression(const string& query) {
    regex FOLLOWSREGEX = regex(R"lit(Follows\s?\(("?\w+"?), ("?\w+"?)\))lit");
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
    regex FOLLOWSSTARREGEX = regex(R"lit(Follows\*\s?\(("?\w+"?), ("?\w+"?)\))lit");
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
    regex PARENTREGEX = regex(R"lit(Parent\s?\(("?\w+"?), ("?\w+"?)\))lit");
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
    regex PARENTSTARREGEX = regex(R"lit(Parent\*\s?\(("?\w+"?), ("?\w+"?)\))lit");
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

void QueryParser::addToSynonymTable(string type, const string& name) {
    if (type == "stmt") {
        this->synonymTable[name] = new StmtEntity("STATEMENT", name);
    } else if (type == "read") {
        this->synonymTable[name] = new ReadEntity(name);
    } else if (type == "print") {
        this->synonymTable[name] = new PrintEntity(name);
    } else if (type == "call") {
        this->synonymTable[name] = new CallEntity(name);
    } else if (type == "while") {
        this->synonymTable[name] = new WhileEntity(name);
    } else if (type == "if") {
        this->synonymTable[name] = new IfEntity(name);
    } else if (type == "assign") {
        this->synonymTable[name] = new AssignEntity(name);
    } else if (type == "variable") {
        this->synonymTable[name] = new VariableEntity(name);
    } else if (type == "constant") {
        this->synonymTable[name] = new ConstantEntity(name);
    } else if (type == "procedure") {
        this->synonymTable[name] = new ProcedureEntity(name);
    }
}

void QueryParser::extractDeclarations(string query) {
	regex EXTRACTDECLARATIONREGEX = regex("(^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) ((\\w|, )+)");
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
                this->addToSynonymTable(type, subname);
                name.erase(0, pos + delimiter.length());
            }
        }
        this->addToSynonymTable(type, name);
	}
}

vector<tuple<string, string>> QueryParser::getSynonymTable() {
    vector<tuple<string, string>> result;
    for (tuple<string, DesignEntity*> t : this->synonymTable) {
        result.emplace_back(get<0>(t), get<1>(t)->getType());
    }
    return result;
}