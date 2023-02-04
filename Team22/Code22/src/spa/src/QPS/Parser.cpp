#include<stdio.h>


#include "PKB/PKB.h"
#include "TNode.h"
#include "Parser.h"

using namespace std;

QueryParser::QueryParser() {

}


SelectExpression QueryParser::parse(string query) {
	vector<Expression> conditions;

	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
		SelectExpression ep({}, conditions);
		return ep;
	} else {
		smatch sm;
		regex RETURNVALUEREGEX = regex("Select (\w+)");
		regex_search(query, sm, RETURNVALUEREGEX);
		
		DesignEntity arg = this->synonymTable[sm.str(1)];

		if (this->containsModifiesExpression(query)) {
			conditions.push_back(this->extractModifiesExpression(query));
		} else if (this->containsUsesExpression(query)) {
			conditions.push_back(this->extractUsesExpression(query));
		}

		return SelectExpression({arg}, conditions);
	}
}

bool QueryParser::isDeclaration(string query) {
	regex ISDECLARATIONREGEX = regex("((^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) ((\\w|, )+))+;");
	return regex_match(query, ISDECLARATIONREGEX);
}

bool QueryParser::containsModifiesExpression(string query) {
	regex CONTAINSMODIFIESREGEX = regex("Modifies\\s?\\(\"?(\\w+)\"?, \"?(\\w+)\"?\\)");
	return distance(sregex_iterator(query.begin(), query.end(), CONTAINSMODIFIESREGEX), std::sregex_iterator()) > 0;
}

bool QueryParser::containsUsesExpression(string query) {
	regex CONTAINSUSESREGEX = regex("Uses\\s?\\(\"?(\\w+)\"?, \"?(\\w+)\"?\\)");
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

ModifiesExpression QueryParser::extractModifiesExpression(string query) {
	regex MODIFIESREGEX = regex("Modifies\\s?\\(\"?(\\w+)\"?, \"?(\\w+)\"?\\)");
	smatch sm;
	regex_search(query, sm, MODIFIESREGEX);

	string arg1 = sm.str(1);
	string arg2 = sm.str(2);

	if (isNumber(arg1)) {
		return ModifiesSExpression(StmtEntity(arg1), NamedEntity(this->synonymTable[arg2].getType(), arg2));
	} else {
		return ModifiesPExpression(NamedEntity(this->synonymTable[arg1].getType(), arg1),  NamedEntity(this->synonymTable[arg2].getType(), arg2));
	}
}


UsesExpression QueryParser::extractUsesExpression(string query) {
	regex USESREGEX = regex("Uses\\s?\\(\"?(\\w+)\"?, \"?(\\w+)\"?\\)");
	smatch sm;
	regex_search(query, sm, USESREGEX);

	string arg1 = sm.str(1);
	string arg2 = sm.str(2);

	if (isNumber(arg1)) {
		return UsesSExpression(StmtEntity(arg1),  NamedEntity(this->synonymTable[arg2].getType(), arg2));
	}
	else {
		return UsesPExpression( NamedEntity(this->synonymTable[arg1].getType(), arg1),  NamedEntity(this->synonymTable[arg2].getType(), arg2));
	}
}

void QueryParser::addToSynonymTable(string type, string name) {
    if (type == "stmt") {
        this->synonymTable[name] = StmtEntity();
    } else if (type == "read") {
        this->synonymTable[name] = ReadEntity();
    } else if (type == "print") {
        this->synonymTable[name] = PrintEntity();
    } else if (type == "call") {
        this->synonymTable[name] = CallEntity();
    } else if (type == "while") {
        this->synonymTable[name] = WhileEntity();
    } else if (type == "if") {
        this->synonymTable[name] = IfEntity();
    } else if (type == "assign") {
        this->synonymTable[name] = AssignEntity();
    } else if (type == "variable") {
        this->synonymTable[name] = VariableEntity(name);
    } else if (type == "constant") {
        this->synonymTable[name] = ConstantEntity(name);
    } else if (type == "procedure") {
        this->synonymTable[name] = ProcedureEntity(name);
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
    for (tuple<string, DesignEntity> t : this->synonymTable) {
        result.emplace_back(get<0>(t), get<1>(t).getType());
    }
    return result;
}