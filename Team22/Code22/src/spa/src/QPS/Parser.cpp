#include<stdio.h>


#include "PKB/PKB.h"
#include "TNode.h"
#include "Parser.h"

using namespace std;

QueryParser::QueryParser() {

}


Expression QueryParser::parse(string query) {
    vector<DesignEntity> des;
	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
		Expression ep(des);
		return ep;
	} else {
		vector<Expression> conditions;
		if (this->containsModifiesExpression(query)) {
			conditions.push_back(this->extractModifiesExpression(query));
		} else if (this->containsUsesExpression(query)) {
			conditions.push_back(this->extractUsesExpression(query));
		}
		return SelectExpression(des, conditions);
	}
}

bool QueryParser::isDeclaration(string query) {
	regex ISDECLARATIONREGEX = regex("((^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) ((\\w|, )+))+;");
	return regex_match(query, ISDECLARATIONREGEX);
}

bool QueryParser::containsModifiesExpression(string query) {
	regex CONTAINSMODIFIESREGEX = regex("Modifies\\(\"(\\w+)\", (\\w+)\\)");
	return false;
}

bool QueryParser::containsUsesExpression(string query) {
	regex CONTAINSUSESREGEX = regex("Uses\\(\"(\\w+)\", (\\w+)\\)");
	return false;
}


ModifiesExpression QueryParser::extractModifiesExpression(string query) {
	regex MODIFIESREGEX = regex("Modifies\\(\"(\\w+)\", \"(\\w+)\"\\)");
    NamedEntity ne("", "");
    ModifiesExpression exp(ne);
	return exp;
}


UsesExpression QueryParser::extractUsesExpression(string query) {
	regex USESREGEX = regex("Uses\\(\"(\\w+)\", \"(\\w+)\"\\)");
	DesignEntity de(" ");
	UsesExpression exp(de);
	return exp;
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