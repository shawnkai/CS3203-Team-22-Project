file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/TestParser.cpp src/PKB/TestPKB.cpp src/QPS/TestQParser.cpp src/QPS/TestQEvaluator.cpp src/PKB/TestPattern/TestAssignPattern.cpp src/PKB/TestDesignAbstractions/TestFollowsDesignAbstraction.cpp src/PKB/TestDesignAbstractions/TestFollowsStarDesignAbstraction.cpp src/PKB/TestDesignEntities/TestProcedureDesignEntity.cpp src/PKB/TestDesignEntities/TestStatementDesignEntity.cpp src/PKB/TestDesignEntities/TestVariableDesignEntity.cpp)

target_link_libraries(unit_testing spa)

