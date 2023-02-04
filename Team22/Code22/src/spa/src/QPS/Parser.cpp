#include<stdio.h>


#include "PKB/PKB.h"
#include "TNode.h"
#include "Parser.h"

QueryParser::QueryParser() {

}


Expression QueryParser::parse(string query) {
	if (this->isDeclaration(query)) {
		this->extractDeclarations(query);
	} else {
		vector<ModifiesExpression> modifiesExpressions = this->extractModifiesExpressions(query);
		vector<UsesExpression> usesExpressions = this->extractUsesExpressions(query);

	}
	Expression ep;
	return ep;
}

bool QueryParser::isDeclaration(string query) {
	regex ISDECLARATIONREGEX = regex("((^|; )(stmt|read|print|call|while|if|assign|variable|constant|procedure) (\\w+))+;");
	return regex_match(query, ISDECLARATIONREGEX);
}


vector<ModifiesExpression> QueryParser::extractModifiesExpressions(string query) {
	regex MODIFIESREGEX = regex("");
	vector<ModifiesExpression> empty;
	return empty;
}


vector<UsesExpression> QueryParser::extractUsesExpressions(string query) {
	regex USESREGEX = regex("");
	vector<UsesExpression> empty;
	return empty;
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
