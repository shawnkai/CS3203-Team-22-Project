file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(integration_testing ${srcs} "src/TestAllComponentsIntegration.cpp" "src/QPS/TestQEvaluator.cpp" src/SP/TestSpIntegrationWithPkb.cpp "src/SP/DesignExtractor/TestAbstractionExtractor.cpp" "src/SP/DesignExtractor/TestAssignExtractor.cpp" "src/SP/DesignExtractor/TestConditionExtractor.cpp" "src/SP/DesignExtractor/TestDesignExtractor.cpp" "src/SP/DesignExtractor/TestIfExtractor.cpp" "src/SP/DesignExtractor/TestNextExtractor.cpp" "src/SP/DesignExtractor/TestPatternPrefixStringExtractor.cpp" "src/SP/DesignExtractor/TestProgramExtractor.cpp" "src/SP/DesignExtractor/TestReadPrintExtractor.cpp" "src/SP/DesignExtractor/TestStmtlstExtractor.cpp" "src/SP/DesignExtractor/TestWhileExtractor.cpp")


target_link_libraries(integration_testing spa)
