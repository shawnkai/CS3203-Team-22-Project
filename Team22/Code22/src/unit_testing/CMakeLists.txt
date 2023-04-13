file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*/*/*/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.hpp")

add_executable(unit_testing ${srcs} src/main.cpp)

target_link_libraries(unit_testing spa)