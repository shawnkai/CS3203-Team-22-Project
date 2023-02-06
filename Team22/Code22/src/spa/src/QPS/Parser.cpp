#include<stdio.h>


#include "PKB/PKB.h"
#include "TNode.h"
#include "Parser.h"

using namespace std;

QueryParser::QueryParser() {

}


SelectExpression* QueryParser::parse(const string& query) {
	vector<Expression*> conditions;

	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
		return new SelectExpression({}, conditions);
	} else {
		smatch sm;
		regex RETURNVALUEREGEX = regex("Select (\\w+)");
		regex_search(query, sm, RETURNVALUEREGEX);
		
		DesignEntity *arg = this->synonymTable[sm.str(1)];

		if (this->containsModifiesExpression(query)) {
			conditions.push_back(this->extractModifiesExpression(query));
		} else if (this->containsUsesExpression(query)) {
			conditions.push_back(this->extractUsesExpression(query));
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

// Returns true if s is a number else false
bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

ModifiesExpression* QueryParser::extractModifiesExpression(const string& query) {
	regex MODIFIESREGEX = regex(R"lit(Modifies\s?\(("?\w+"?), ("?\w+"?)\))lit");
	smatch sm;
	regex_search(query, sm, MODIFIESREGEX);

	string arg1 = sm.str(1);
	string arg2 = sm.str(2);

	if (isNumber(arg1)) {
        auto *a1 = new StmtEntity(stoi(arg1));
        auto *a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
		return new ModifiesSExpression(a1, a2);;
	} else {
        NamedEntity *a1;
        if (arg1.find('\"') != string::npos) {
            arg1.erase(remove(arg1.begin(), arg1.end(), '\"'), arg1.end());
            a1 = new NamedEntity("ident", arg1);
        } else {
            a1 = new NamedEntity(this->synonymTable[arg1]->getType(), arg1);
        }

        NamedEntity *a2;
        if (arg2.find('\"') != string::npos) {
            arg2.erase(remove(arg2.begin(), arg2.end(), '\"'), arg2.end());
            a2 = new NamedEntity("ident", arg2);
        } else {
            a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
        }

		return new ModifiesPExpression(a1,  a2);;
	}
}


UsesExpression* QueryParser::extractUsesExpression(const string& query) {
	regex USESREGEX = regex(R"lit(Uses\s?\(("?\w+"?), ("?\w+"?)\))lit");
	smatch sm;
	regex_search(query, sm, USESREGEX);

	string arg1 = sm.str(1);
	string arg2 = sm.str(2);

	if (isNumber(arg1)) {
        auto *a1 = new StmtEntity(stoi(arg1));
        auto *a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
		return new UsesSExpression(a1,  a2);
	}
	else {
        NamedEntity *a1;
        if (arg1.find('\"') != string::npos) {
            arg1.erase(remove(arg1.begin(), arg1.end(), '\"'), arg1.end());
            a1 = new NamedEntity("ident", arg1);
        } else {
            a1 = new NamedEntity(this->synonymTable[arg1]->getType(), arg1);
        }

        NamedEntity *a2;
        if (arg2.find('\"') != string::npos) {
            arg2.erase(remove(arg2.begin(), arg2.end(), '\"'), arg2.end());
            a2 = new NamedEntity("ident", arg2);
        } else {
            a2 = new NamedEntity(this->synonymTable[arg2]->getType(), arg2);
        }

		return new UsesPExpression(a1,  a2);
	}
}

void QueryParser::addToSynonymTable(string type, const string& name) {
    if (type == "stmt") {
        this->synonymTable[name] = new StmtEntity();
    } else if (type == "read") {
        this->synonymTable[name] = new ReadEntity();
    } else if (type == "print") {
        this->synonymTable[name] = new PrintEntity();
    } else if (type == "call") {
        this->synonymTable[name] = new CallEntity();
    } else if (type == "while") {
        this->synonymTable[name] = new WhileEntity();
    } else if (type == "if") {
        this->synonymTable[name] = new IfEntity();
    } else if (type == "assign") {
        this->synonymTable[name] = new AssignEntity();
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