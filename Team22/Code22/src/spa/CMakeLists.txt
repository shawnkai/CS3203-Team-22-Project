file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/DesignExtractor.h src/Tokenizer.h src/Tokenizer.cpp src/Token.h src/SPDriver.h src/SPDriver.cpp "src/EntityExtractor.cpp" "src/EntityExtractor.h" "src/ReadExtractor.cpp" "src/ReadExtractor.h" "src/VariableExtractor.cpp" "src/VariableExtractor.h"  )
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


