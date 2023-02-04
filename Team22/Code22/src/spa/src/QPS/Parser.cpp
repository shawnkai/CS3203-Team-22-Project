#include<stdio.h>


#include "PKB/PKB.h"
#include "TNode.h"
#include "Parser.h"

QueryParser::QueryParser() {

}


Expression QueryParser::parse(string query) {
	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
		Expression ep;
		return ep;
	} else {
		vector<Expression> conditions;
		if (this->containsModifiesExpression(query)) {
			conditions.push_back(this->extractModifiesExpression(query));
		} else if (this->containsUsesExpression(query)) {
			conditions.push_back(this->extractUsesExpression(query));
		}
		return SelectExpression(conditions);
	}
}

bool QueryParser::isDeclaration(string query) {
	regex ISDECLARATIONREGEX = regex("((^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) (\\w+))+;");
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
	regex MODIFIESREGEX = regex("Modifies\\(\"(\\w+)\", \"(\\w+)\")");
    NamedEntity ne("", "");
    ModifiesExpression exp(ne);
	return exp;
}


UsesExpression QueryParser::extractUsesExpression(string query) {
	regex USESREGEX = regex("Uses\(\"(\\w+)\", \"(\\w+)\"\)");
	vector<UsesExpression> empty;
	NamedEntity ne("", "");
	UsesExpression exp(ne);
	return exp;
}

void QueryParser::extractDeclarations(string query) {
	regex EXTRACTDECLARATIONREGEX = regex("(^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) (\\w+)");
	smatch sm;
	auto begin = sregex_iterator(query.begin(), query.end(), EXTRACTDECLARATIONREGEX);
    auto end = sregex_iterator();

	for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;                                                 
        string type = match.str(2);
        string name =  match.str(3);

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
}
