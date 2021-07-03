
cmake_minimum_required(VERSION 3.10)
project(accparser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

set(ACCPARSER_VERSION_MAJOR 0)
set(ACCPARSER_VERSION_MINOR 1)
set(ACCPARSER_VERSION ${ACCPARSER_VERSION_MAJOR}.${ACCPARSER_VERSION_MINOR})

find_program(NAMES antlr4)

# Not used, but keep this for the purpose to keep track of the original source files
set(ACCPARSER_SOURCE_FILES
    src/acclexer.g4
    src/accparser.g4
    src/OpenACCIR.h
    src/OpenACCIR.cpp
    main.cpp
    )

set(ACCPARSER_GRAMMAR_FILES
    ${CMAKE_SOURCE_DIR}/src/acclexer.g4
    ${CMAKE_SOURCE_DIR}/src/accparser.g4
    )

# OpenACCIR source files
set(ACCIR_SOURCE_FILES
    src/OpenACCIR.h
    src/OpenACCIR.cpp
    )

# tools based on accparser
set(ACCPARSER_TOOLS
    )

set(ACCPARSER_GRAMMAR_TARGET_FILES
  acclexer.cpp
  accparser.cpp
)

add_custom_command(OUTPUT
    ${ACCPARSER_GRAMMAR_TARGET_FILES}
    COMMAND
    antlr4 ${ACCPARSER_GRAMMAR_FILES} -Werror -Dlanguage=Cpp -listener -visitor -o ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "${ACCPARSER_GRAMMAR_FILES}"
    )

add_custom_target(accparser_grammar DEPENDS ${ACCPARSER_GRAMMAR_TARGET_FILES})

add_compile_options(-Wall)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(SYSTEM /usr/include/antlr4-runtime)

# The accparser library for installation and distribution
add_library(accparser SHARED ${ACCIR_SOURCE_FILES})
add_dependencies(accparser accparser_grammar)
target_link_libraries(accparser
    antlr4-runtime
    )

add_executable(main.out main.cpp ${ACCPARSER_GRAMMAR_TARGET_FILES})
add_dependencies(main.out accparser)
target_link_libraries(main.out
    antlr4-runtime
    )

set(accparser_targets accparser)
set(executable_targets
    main.out
    )

# Install headers and libraries
install(FILES
        src/OpenACCIR.h
        DESTINATION include)
install(TARGETS ${accparser_targets}
        LIBRARY DESTINATION lib
        )
install(TARGETS ${executable_targets}
        RUNTIME DESTINATION bin
        )
