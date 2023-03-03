//
// Created by Jai Lulla  on 20/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntityDatabase.h"
#include "PKB/DesignEntities/DesignEntitiesDatabase/DesignEntitiesDatabaseFactory.h"

using namespace std;

TEST_CASE("Test 1: Returns Variable Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase("VARIABLE");
        VariableDatabase* vdb = dynamic_cast<VariableDatabase*>(db);

        REQUIRE (vdb != nullptr);
    }
}

TEST_CASE("Test 2: Returns Constant Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase("CONSTANT");
        ConstantDatabase* cdb = dynamic_cast<ConstantDatabase*>(db);

        REQUIRE (cdb != nullptr);
    }
}

TEST_CASE("Test 3: Returns Procedure Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase("PROCEDURE");
        ProcedureDatabase* pdb = dynamic_cast<ProcedureDatabase*>(db);

        REQUIRE (pdb != nullptr);
    }
}

TEST_CASE("Test 4: Returns Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase("STATEMENT");
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db);

        REQUIRE (sdb != nullptr);
    }
}

TEST_CASE("Test 5: Returns Assignment Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("ASSIGNMENT") ;

        AssignmentStatementDatabase* asdb = dynamic_cast<AssignmentStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(asdb) ;

        REQUIRE(((asdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 6: Returns Call Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("CALL") ;

        CallStatementDatabase* csdb = dynamic_cast<CallStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(csdb) ;

        REQUIRE(((csdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 7: Returns If Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("IF") ;

        IfStatementDatabase* isdb = dynamic_cast<IfStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(isdb) ;

        REQUIRE(((isdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 8: Returns Print Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("PRINT") ;

        PrintStatementDatabase* psdb = dynamic_cast<PrintStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(psdb) ;

        REQUIRE(((psdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 9: Returns Read Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("READ") ;

        ReadStatementDatabase* rsdb = dynamic_cast<ReadStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(rsdb) ;

        REQUIRE(((rsdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 10: Returns Print Statement Design Entity Database") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase ("WHILE") ;

        WhileStatementDatabase* wsdb = dynamic_cast<WhileStatementDatabase*>(db) ;
        StatementDatabase* sdb = dynamic_cast<StatementDatabase*>(db) ;

        StatementDatabase* sdb1 = dynamic_cast<StatementDatabase*>(wsdb) ;

        REQUIRE(((wsdb != nullptr) && (sdb != nullptr) && (sdb1 != nullptr))) ;
    }
}

TEST_CASE("Test 11: Returns Null Pointer For Any Unknown Design Entity Passed In") {
    SECTION ("") {
        DesignEntityDatabase* db = DesignEntitiesDatabaseFactory::getEntityDatabase("TRIAL");

        REQUIRE (db == nullptr);
    }
}
