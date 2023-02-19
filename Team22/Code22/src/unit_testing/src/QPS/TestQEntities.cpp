//
// Created by Tanishq Sharma on 20/2/23.
//

#include "QPS/Entities.h"
#include "catch.hpp"
#include "QPS/Exceptions.h"

using namespace std;

TEST_CASE("TestCase1_StmtEntityAlphanumericSynonym_Success") {
    bool throwsException = false;

    try {
        StmtEntity* s = new StmtEntity("TESTTYPE", "v123x");
    } catch (ParseException& e) {
        throwsException = true;
    }

    REQUIRE(not throwsException);
}

TEST_CASE("TestCase2_NamedEntityAlphanumericSynonym_Success") {
    bool throwsException = false;

    try {
        NamedEntity* s = new NamedEntity("TESTTYPE", "12abc");
    } catch (ParseException& e) {
        throwsException = true;
    }

    REQUIRE(not throwsException);
}

TEST_CASE("TestCase3_StmtEntityPositiveInteger_Success") {
    bool throwsException = false;

    try {
        StmtEntity* s = new StmtEntity(23);
    } catch (ParseException& e) {
        throwsException = true;
    }

    REQUIRE(not throwsException);
}


TEST_CASE("TestCase4_StmtEntitySynonymNotAlphanumeric_SyntaxError") {
    bool throwsException = false;

    try {
        StmtEntity* s = new StmtEntity("TESTTYPE", "v123_x");
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase5_NamedEntitySynonymNotAlphanumeric_SyntaxError") {
    bool throwsException = false;

    try {
        NamedEntity* s = new NamedEntity("TESTTYPE", "12*abc");
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}

TEST_CASE("TestCase6_StmtEntityNegativeInteger_SemanticError") {
    bool throwsException = false;

    try {
        StmtEntity* s = new StmtEntity(-4);
    } catch (SemanticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


TEST_CASE("TestCase7_IdentNamedEntityMissingOpeningQuote_SyntaxError") {
    bool throwsException = false;

    try {
        NamedEntity* s = new NamedEntity("ident", "var\"");
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}


TEST_CASE("TestCase8_IdentNamedEntityMissingClosingQuote_SyntaxError") {
    bool throwsException = false;

    try {
        NamedEntity* s = new NamedEntity("ident", "\"var");
    } catch (SyntacticException& e) {
        throwsException = true;
    }

    REQUIRE(throwsException);
}




