//
// Created by Jai Lulla  on 5/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionDatabase.h"
#include "PKB/DesignAbstractions/DesignAbstractionsDatabase/DesignAbstractionsDatabaseFactory.h"

using namespace std;

TEST_CASE("Test 1: Get Follows Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("FOLLOWS", "_");

    FollowsDatabase *fdb = dynamic_cast<FollowsDatabase *>(db);

    REQUIRE(fdb != nullptr);
}

TEST_CASE("Test 2: Get FollowsStar Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("FOLLOWSSTAR", "_");

    FollowsStarDatabase *fsdb = dynamic_cast<FollowsStarDatabase *>(db);

    REQUIRE(fsdb != nullptr);
}

TEST_CASE("Test 3: Get Parent Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("PARENT", "_");

    ParentDatabase *pdb = dynamic_cast<ParentDatabase *>(db);

    REQUIRE(pdb != nullptr);
}

TEST_CASE("Test 4: Get ParentStar Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("PARENTSTAR", "_");

    ParentStarDatabase *psdb = dynamic_cast<ParentStarDatabase *>(db);

    REQUIRE(psdb != nullptr);
}

TEST_CASE("Test 5: Get ParentStar Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("PARENTSTAR", "_");

    ParentStarDatabase *psdb = dynamic_cast<ParentStarDatabase *>(db);

    REQUIRE(psdb != nullptr);
}

TEST_CASE("Test 6: Get Calls Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("CALLS", "_");

    CallsDatabase *cdb = dynamic_cast<CallsDatabase *>(db);

    REQUIRE(cdb != nullptr);
}

TEST_CASE("Test 7: Get CallsStar Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("CALLSSTAR", "_");

    CallsStarDatabase *csdb = dynamic_cast<CallsStarDatabase *>(db);

    REQUIRE(csdb != nullptr);
}

TEST_CASE("Test 8: Get InverseCalls Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("INVERSECALLS", "_");

    InverseCallsDatabase *icdb = dynamic_cast<InverseCallsDatabase *>(db);

    REQUIRE(icdb != nullptr);
}

TEST_CASE("Test 9: Get Next Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("NEXT", "_");

    NextDatabase *ndb = dynamic_cast<NextDatabase *>(db);

    REQUIRE(ndb != nullptr);
}

TEST_CASE("Test 10: Get Assignment Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "ASSIGNMENT");

    AssignmentModifiesDatabase *amdb = dynamic_cast<AssignmentModifiesDatabase *>(db);

    REQUIRE(amdb != nullptr);
}

TEST_CASE("Test 11: Get If Statement Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "IF");

    IfStatementModifiesDatabase *ismdb = dynamic_cast<IfStatementModifiesDatabase *>(db);

    REQUIRE(ismdb != nullptr);
}

TEST_CASE("Test 12: Get Procedure Call Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "PROCEDURECALL");

    ProcedureCallModifiesDatabase *pcmdb = dynamic_cast<ProcedureCallModifiesDatabase *>(db);

    REQUIRE(pcmdb != nullptr);
}

TEST_CASE("Test 13: Get Procedure Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "PROCEDURE");

    ProcedureModifiesDatabase *pmdb = dynamic_cast<ProcedureModifiesDatabase *>(db);

    REQUIRE(pmdb != nullptr);
}

TEST_CASE("Test 14: Get Read Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "READ");

    ReadModifiesDatabase *rmdb = dynamic_cast<ReadModifiesDatabase *>(db);

    REQUIRE(rmdb != nullptr);
}

TEST_CASE("Test 15: Get Statement Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "STATEMENT");

    StatementModifiesDatabase *smdb = dynamic_cast<StatementModifiesDatabase *>(db);

    REQUIRE(smdb != nullptr);
}

TEST_CASE("Test 16: Get While Statement Modifies Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("MODIFIES",
                                                                                              "WHILE");

    WhileStatementModifiesDatabase *wsmdb = dynamic_cast<WhileStatementModifiesDatabase *>(db);

    REQUIRE(wsmdb != nullptr);
}

TEST_CASE("Test 17: Get Assignment Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "ASSIGNMENT");

    AssignmentUsesDatabase *audb = dynamic_cast<AssignmentUsesDatabase *>(db);

    REQUIRE(audb != nullptr);
}

TEST_CASE("Test 18: Get If Statement Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "IF");

    IfStatementUsesDatabase *isudb = dynamic_cast<IfStatementUsesDatabase *>(db);

    REQUIRE(isudb != nullptr);
}

TEST_CASE("Test 19: Get Print Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "PRINT");

    PrintUsesDatabase *pudb = dynamic_cast<PrintUsesDatabase *>(db);

    REQUIRE(pudb != nullptr);
}

TEST_CASE("Test 20: Get Procedure Call Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "PROCEDURECALL");

    ProcedureCallUsesDatabase *pcudb = dynamic_cast<ProcedureCallUsesDatabase *>(db);

    REQUIRE(pcudb != nullptr);
}

TEST_CASE("Test 21: Get Procedure Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "PROCEDURE");

    ProcedureUsesDatabase *pudb = dynamic_cast<ProcedureUsesDatabase *>(db);

    REQUIRE(pudb != nullptr);
}

TEST_CASE("Test 22: Get Statement Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "STATEMENT");

    StatementUsesDatabase *sudb = dynamic_cast<StatementUsesDatabase *>(db);

    REQUIRE(sudb != nullptr);
}

TEST_CASE("Test 23: Get While Statement Uses Database") {
    DesignAbstractionDatabase *db = DesignAbstractionsDatabaseFactory::getAbstractionDatabase("USES",
                                                                                              "WHILE");

    WhileStatementUsesDatabase *wsudb = dynamic_cast<WhileStatementUsesDatabase *>(db);

    REQUIRE(wsudb != nullptr);
}
