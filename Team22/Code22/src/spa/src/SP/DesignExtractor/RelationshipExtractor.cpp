#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

#include "RelationshipExtractor.h"

void RelationshipExtractor::extractModifiesorUsesAbstraction(string type1, PKB pkbinstance, string procedureName, string variableName, int lineNumOfVariable) {
    std::string inverseCallsStr = "INVERSECALLS";
    std::string callStr = "CALL";

    pkbinstance.addDesignAbstraction(type1, make_tuple(procedureStr, procedureName, std::to_string(lineNumOfVariable)));
    pkbinstance.addDesignAbstraction(type1, make_tuple(procedureStr, variableName, procedureName));
    cout << std::to_string(lineNumOfVariable) + " " + type1 + " procedure " + procedureName << endl;
    cout << variableName + " " + type1 + " procedure " + procedureName << endl;

    Result result1 = pkbinstance.getDesignAbstraction(inverseCallsStr, make_pair("_", procedureName));
    std::vector<std::string> vector1 = result1.getQueryResult();
    for (int i = 0; i < vector1.size(); i++) {
        if (vector1[i] != "none") {
            pkbinstance.addDesignAbstraction(type1, make_tuple(procedureStr, vector1[i], std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(type1, make_tuple(procedureStr, variableName, vector1[i]));
            cout << std::to_string(lineNumOfVariable) + " " + type1 + " procedure " + vector1[i] << endl;
            cout << variableName + " " + type1 + " procedure " + vector1[i] << endl;
        }
        Result result3 = pkbinstance.getDesignEntity(callStr, vector1[i]);
        std::vector<std::string> vector3 = result3.getQueryResult();
        for (int j = 0; j < vector3.size(); j++) {
            if (vector3[j] != "none") {
                pkbinstance.addDesignAbstraction(type1, make_tuple(procedurecallStr, vector3[j], std::to_string(lineNumOfVariable)));
                pkbinstance.addDesignAbstraction(type1, make_tuple(procedurecallStr, variableName, vector3[j]));
                pkbinstance.addDesignAbstraction(type1, make_tuple(statementStr, variableName, vector3[j]));

                cout << std::to_string(lineNumOfVariable) + " " + type1 + " procedureCall " + vector3[j] << endl;
            }
        }
    }

    Result result2 = pkbinstance.getDesignEntity(callStr, procedureName);
    std::vector<std::string> vector2 = result2.getQueryResult();
    for (int i = 0; i < vector2.size(); i++) {
        if (vector2[i] != "none") {
            pkbinstance.addDesignAbstraction(type1, make_tuple(procedurecallStr, vector2[i], std::to_string(lineNumOfVariable)));
            pkbinstance.addDesignAbstraction(type1, make_tuple(procedurecallStr, variableName, vector2[i]));
            pkbinstance.addDesignAbstraction(type1, make_tuple(statementStr, variableName, vector2[i]));

            cout << std::to_string(lineNumOfVariable) + " " + type1 + " procedureCall " + vector2[i] << endl;
        }
    }
}

void RelationshipExtractor::extractContainerUsesOrModifiesAbstraction(string type1, vector<string> ifContainers, vector<string> whileContainers, PKB pkbinstance, string variableName) {
    if (whileContainers.size() != 0) {
        for (int i = 0; i < whileContainers.size(); i++) {
            cout << whileContainers[i] << endl;
            pkbinstance.addDesignAbstraction(type1, make_tuple(whileStr, variableName, whileContainers[i]));
            pkbinstance.addDesignAbstraction(type1, make_tuple(statementStr, variableName, whileContainers[i]));
        }
    }
    if (ifContainers.size() != 0) {
        for (int i = 0; i < ifContainers.size(); i++) {
            cout << ifContainers[i] << endl;
            pkbinstance.addDesignAbstraction(type1, make_tuple(ifStr, variableName, ifContainers[i]));
            pkbinstance.addDesignAbstraction(type1, make_tuple(statementStr, variableName, ifContainers[i]));
        }
    }
}



