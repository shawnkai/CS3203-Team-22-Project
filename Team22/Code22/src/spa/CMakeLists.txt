file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.cpp")

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.h")

add_library(spa ${srcs} ${headers} src/QPS/Entities/NamedEntity/NamedEntity.cpp src/QPS/Entities/NamedEntity/NamedEntity.h src/QPS/Entities/StmtRef/StmtRef.cpp src/QPS/Entities/StmtRef/StmtRef.h src/QPS/Optimizer/Optimizer.h src/QPS/Optimizer/parallel.h src/QPS/Optimizer/ConcurrentVector.h)

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


