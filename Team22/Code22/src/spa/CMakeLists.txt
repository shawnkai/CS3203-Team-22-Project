file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/PKB/DesignAbstractions/DesignAbstractionsFactory.h src/PKB/DesignEntities/DesignEntitiesFactory.h src/PKB/DesignAbstractions/DesignAbstractions.h src/Result.h src/Result.cpp src/PKB/DesignAbstractions/DesignAbstractions.cpp src/PKB/DesignAbstractions/DesignAbstractionsFactory.cpp src/PKB/DesignEntities/DesignEntitiesFactory.cpp src/PKB/DesignEntities/DesignEntities.h src/PKB/DesignEntities/DesignEntities.cpp src/PKB/PKB.cpp)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


