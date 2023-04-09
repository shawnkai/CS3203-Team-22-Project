#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#include "ProgramExtractor.h"

/* std::map<string, vector<string>> mapOfWhileForCallStmts;
std::map<string, vector<string>> mapOfIfForCallStmts;
std::map<string, vector<string>> mapOfModifiedVarforCalls;
std::map<string, vector<string>> mapOfUsedVarforCalls;
vector<string> callStmts;*/

/**
 * Extracts the procedures from the Abstract Syntax Tree and call Abstraction
 * Extractor to extract the abstractions and entites from each procedure. 
 * The call and callStar relationships are added to the Program Knowledge Base.
 *
 * @param root The root node of the Abstract Syntax Tree, of type TNode.
 * @param pkbinstance An instance of Program Knowledge Base.
 */
void ProgramExtractor::extractAbstraction() {
    std::map<std::string, std::vector<string>> mapOfCalls;
    std::vector<string> vectorOfProcedureNames;
    std::string underlineStr = "_";

    if (root.nodeType != TokenType::PROGRAM) {
        cout << "something went wrong" << endl;
    } else {
        int noOfProcedures;
        noOfProcedures = (root.children).size();
        cout << std::to_string(noOfProcedures) << endl;
        if (noOfProcedures == 0) {
            cout << "there are no procedures in this program" << endl;
        } else {
            std::vector<TNode> procedures = root.children;
            for (int i = 0; i < noOfProcedures; i++) {
                TNode procedureNode = procedures[i];
                std::string procedureName = procedureNode.stringId;
                vectorOfProcedureNames.push_back(procedureName);
                queue<TNode> queueOfNodes;
                queueOfNodes.push(procedureNode);
                while (queueOfNodes.size() > 0) {
                    TNode current = queueOfNodes.front();
                    if (current.nodeType == TokenType::CALL) {
                        std::string procedureCalled = current.stringId;
                        int callLineNo = current.stmtNumber;
                        if (mapOfCalls.count(procedureName) > 0) {
                            std::vector<string> vectorPrev = mapOfCalls.at(procedureName);
                            vectorPrev.push_back(procedureCalled);
                            mapOfCalls[procedureName] = vectorPrev;
                        } else {
                            std::vector<string> vectorNew;
                            vectorNew.push_back(procedureCalled);
                            mapOfCalls[procedureName] = vectorNew;
                        }
                        pkbinstance.addDesignAbstraction("CALLS", make_tuple(underlineStr, procedureName, procedureCalled));
                        cout << procedureName + " calls " + procedureCalled << endl;
                        pkbinstance.addDesignEntity("CALL", make_tuple(procedureCalled, std::to_string(callLineNo)));
                        pkbinstance.addDesignEntity("STATEMENT", make_tuple(procedureCalled, std::to_string(callLineNo)));
                    } else {
                    }
                    std::vector<TNode> children1 = current.children;
                    if (children1.size() > 0) {
                        for (int j = 0; j < children1.size(); j++) {
                            queueOfNodes.push(children1[j]);
                        }
                    }
                    queueOfNodes.pop();
                }
            }

            extractCallStarAbstractions(noOfProcedures, vectorOfProcedureNames, mapOfCalls, pkbinstance);
            
            for (int i = 0; i < noOfProcedures; i++) {
                std::vector<TNode> childNodes = root.children;
                TNode currentNode = childNodes[i];
                std::string procedureName = currentNode.stringId;
                ExtractorFactory factory1;                
                std::vector<string> ifContainer = std::vector<string>(0);
                std::vector<string> whileContainer = std::vector<string>(0);
                std::map<string, vector<string>> information = constructMap(ifContainer, whileContainer, procedureName, std::to_string(0));
                auto abstractionExtractor = factory1.createExtractor(currentNode, information, pkbinstance);
                abstractionExtractor->extractAbstraction();
                //AbstractionExtractor abstractionExtractor;
                //abstractionExtractor.extractAbstraction(currentNode, pkbinstance, procedureName);
            }
        }
    }
};

void ProgramExtractor::extractCallStarAbstractions(int noOfProcedures, std::vector<string> vectorOfProcedureNames, std::map<std::string, std::vector<string>> mapOfCalls, PKB pkbinstance) {
    if (noOfProcedures == 1) {

    } else {
        for (int i = 0; i < noOfProcedures; i++) {
            std::string procedureName = vectorOfProcedureNames[i];
            queue<std::string> queueOfCalls;
            vector<std::string> vectorOfCallsSTAR;
            std::vector<string> vector1;
            if (mapOfCalls.count(procedureName) > 0) {
                vector1 = mapOfCalls.at(procedureName);
            } else {
            }
            set<std::string> setOfCalls;
            if (vector1.size() == 0) {
            } else {
                for (int j = 0; j < vector1.size(); j++) {
                    queueOfCalls.push(vector1[j]);
                    setOfCalls.insert(vector1[j]);
                    vectorOfCallsSTAR.push_back(vector1[j]);
                }
                while (queueOfCalls.size() > 0) {
                    std::string proceduareCalled = queueOfCalls.front();
                    std::vector<string> vector2;
                    if (mapOfCalls.count(proceduareCalled) > 0) {
                        vector2 = mapOfCalls.at(proceduareCalled);
                    } else {
                    }
                    for (int k = 0; k < vector2.size(); k++) {
                        if (setOfCalls.count(vector2[k]) == 1) {

                        } else {
                            queueOfCalls.push(vector2[k]);
                            setOfCalls.insert(vector2[k]);
                            vectorOfCallsSTAR.push_back(vector2[k]);
                        }
                    }
                    queueOfCalls.pop();
                }
            }
            for (int j = 0; j < vectorOfCallsSTAR.size(); j++) {
                /* if (procedureName == vectorOfCallsSTAR[j]) {
                    throw std::invalid_argument("SIMPLE source is invalid because procedure calls itself");
                }*/
                std::string underlineStr = "_";
                pkbinstance.addDesignAbstraction("CALLSSTAR", make_tuple(underlineStr, procedureName, vectorOfCallsSTAR[j]));
                pkbinstance.addDesignAbstraction("INVERSECALLS", make_tuple(underlineStr, vectorOfCallsSTAR[j], procedureName));
                cout << procedureName + " callsStar " + vectorOfCallsSTAR[j] << endl;
            }
        }
    }
}

void ProgramExtractor::extractCallAbstraction(PKB pkbinstance) {
    
    std::map<string, vector<string>> mapOfWhileForCallStmts = Extractor::getmapOfWhileForCallStmts();
    std::map<string, vector<string>> mapOfIfForCallStmts = Extractor::getmapOfIfForCallStmts();
    unordered_map<string, unordered_set<string>> mapOfModifiedVarforCalls = pkbinstance.getAllVariablesCapturedByDesignAbstraction(modifiesStr, "PROCEDURECALL");
    unordered_map<string, unordered_set<string>> mapOfUsedVarforCalls = pkbinstance.getAllVariablesCapturedByDesignAbstraction(usesStr, "PROCEDURECALL");
    vector<Result> callStmts1 = pkbinstance.getAllDesignEntity("CALL");
    vector<string> callStmts;
    callStmts = getAllCallStmts(callStmts1);

    /* std::string statementStr = "STATEMENT";
    std::string procedureStr = "PROCEDURE";
    std::string procedurecallStr = "PROCEDURECALL";
    std::string ifStr = "IF";
    std::string whileStr = "WHILE";*/
    int noOfcalls = callStmts.size();
    if (noOfcalls == 0) {

    } else {

        for (int i = 0; i < noOfcalls; i++) {
            //int callstmt = callStmts[i];
            //string callStmtStr = std::to_string(callstmt);
            string callStmtStr = callStmts[i];
            if (mapOfModifiedVarforCalls.count(callStmtStr) > 0) {
                unordered_set<string> modifiedVars = mapOfModifiedVarforCalls.at(callStmtStr);
                if (modifiedVars.size() == 0) {

                } else {
                    for (const auto &varName1: modifiedVars) {
                        //for (int j = 0; j < modifiedVars.size(); j++) {
                        if (mapOfWhileForCallStmts.count(callStmtStr) > 0) {                         //callstmt
                            vector<string> whileContainers1 = mapOfWhileForCallStmts.at(callStmtStr);//callstmt
                            if (whileContainers1.size() > 0) {
                                for (int k = 0; k < whileContainers1.size(); k++) {
                                    pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(whileStr, varName1, whileContainers1[k]));
                                    pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, varName1, whileContainers1[k]));
                                    cout << varName1 + "modifies while" + whileContainers1[k] << endl;
                                }
                            }
                        }
                        if (mapOfIfForCallStmts.count(callStmtStr) > 0) {
                            vector<string> ifContainers1 = mapOfIfForCallStmts.at(callStmtStr);//callstmt
                            if (ifContainers1.size() > 0) {
                                for (int k = 0; k < ifContainers1.size(); k++) {
                                    pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(ifStr, varName1, ifContainers1[k]));
                                    pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, varName1, ifContainers1[k]));
                                    cout << varName1 + "modifies if" + ifContainers1[k] << endl;
                                }
                            }
                        }
                    }
                }
                
            } else {
            }
            if (mapOfUsedVarforCalls.count(callStmtStr) > 0) {
                unordered_set<string> usedVars = mapOfUsedVarforCalls.at(callStmtStr);
                if (usedVars.size() == 0) {
                } else {
                    for (const auto &varName1: usedVars) {
                        if (mapOfWhileForCallStmts.count(callStmtStr) > 0) {                         //callstmt
                            vector<string> whileContainers1 = mapOfWhileForCallStmts.at(callStmtStr);//callstmt
                            if (whileContainers1.size() > 0) {
                                for (int k = 0; k < whileContainers1.size(); k++) {
                                    pkbinstance.addDesignAbstraction("USES", make_tuple(whileStr, varName1, whileContainers1[k]));
                                    pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, varName1, whileContainers1[k]));
                                    cout << varName1 + "uses while" + whileContainers1[k] << endl;
                                }
                            }
                        }
                        if (mapOfIfForCallStmts.count(callStmtStr) > 0) {                      //callstmt
                            vector<string> ifContainers1 = mapOfIfForCallStmts.at(callStmtStr);//callstmt
                            if (ifContainers1.size() > 0) {
                                for (int k = 0; k < ifContainers1.size(); k++) {
                                    pkbinstance.addDesignAbstraction("USES", make_tuple(ifStr, varName1, ifContainers1[k]));
                                    pkbinstance.addDesignAbstraction("USES", make_tuple(statementStr, varName1, ifContainers1[k]));
                                    cout << varName1 + "uses if" + ifContainers1[k] << endl;
                                }
                            }
                        }
                    }
                
                }
                
            } else {
            }
        }
    }
};

vector<string> ProgramExtractor::getAllCallStmts(vector<Result> callStmts1) {
    vector<string> callStmts2;
    if (callStmts1.size() == 0) {
        return callStmts2;
    } else {
        for (int i = 0; i < callStmts1.size(); i++) {
            Result currCallResult = callStmts1[i];
            vector<string> vectorOfCallLines = currCallResult.getQueryResult();
            if (vectorOfCallLines.size() == 0) {

            } else {
                for (int j = 0; j < vectorOfCallLines.size(); j++) {
                    callStmts2.push_back(vectorOfCallLines[j]);
                }
            
            }
        }
        return callStmts2;
    
    }

}

/*
void ProgramExtractor::extractCALLInContainers(string type1, int callstmt, string callStmtStr, std::map<string, vector<string>> mapOfModifiedVarforCalls, std::map<string, vector<string>> mapOfUsedVarforCalls, std::map<int, vector<int>> mapOfWhileForCallStmts, PKB pkbinstance) {
    if (mapOfModifiedVarforCalls.count(callStmtStr) > 0) {
        vector<string> modifiedVars = mapOfModifiedVarforCalls.at(callStmtStr);
        for (int j = 0; j < modifiedVars.size(); j++) {
            if (mapOfWhileForCallStmts.count(callstmt) > 0) {
                vector<int> whileContainers1 = mapOfWhileForCallStmts.at(callstmt);
                if (whileContainers1.size() > 0) {
                    for (int k = 0; k < whileContainers1.size(); k++) {
                        pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(whileStr, modifiedVars[j], std::to_string(whileContainers1[k])));
                        pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, modifiedVars[j], std::to_string(whileContainers1[k])));
                        cout << modifiedVars[j] + "modifies while" + std::to_string(whileContainers1[k]) << endl;
                    }
                }
            }
            if (mapOfIfForCallStmts.count(callstmt) > 0) {
                vector<int> ifContainers1 = mapOfIfForCallStmts.at(callstmt);
                if (ifContainers1.size() > 0) {
                    for (int k = 0; k < ifContainers1.size(); k++) {
                        pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(ifStr, modifiedVars[j], std::to_string(ifContainers1[k])));
                        pkbinstance.addDesignAbstraction("MODIFIES", make_tuple(statementStr, modifiedVars[j], std::to_string(ifContainers1[k])));
                        cout << modifiedVars[j] + "modifies if" + std::to_string(ifContainers1[k]) << endl;
                    }
                }
            }
        }
    } else {
    }
};*/