
cmake_minimum_required(VERSION 3.10)
project(accparser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

set(ACCPARSER_VERSION_MAJOR 0)
set(ACCPARSER_VERSION_MINOR 1)
set(ACCPARSER_VERSION ${ACCPARSER_VERSION_MAJOR}.${ACCPARSER_VERSION_MINOR})

find_program(NAMES antlr4)

add_subdirectory(tests)
enable_testing()
set(CMAKE_CTEST_ARGUMENTS --output-on-failure)

# Not used, but keep this for the purpose to keep track of the original source files
set(ACCPARSER_SOURCE_FILES
    src/acclexer.g4
    src/accparser.g4
    src/OpenACCIR.h
    src/OpenACCIR.cpp
    main.cpp
    )

set(ACCPARSER_GRAMMAR_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/acclexer.g4
    ${CMAKE_CURRENT_SOURCE_DIR}/src/accparser.g4
    )

# OpenACCIR source files
set(ACCIR_SOURCE_FILES
    src/OpenACCASTConstructor.cpp
    src/OpenACCIR.cpp
    src/OpenACCIRToString.cpp
    )

# tools based on accparser
set(ACCPARSER_TOOLS
    utils/omp-translator/OpenMPTranslator.cpp
    utils/omp-translator/driver.cpp
    )
if (USE_OMPPARSER)
    set(ACCIR_SOURCE_FILES ${ACCIR_SOURCE_FILES} ${ACCPARSER_TOOLS})
    if (NOT USE_REX)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils/omp-translator/ompparser)
    endif()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils/omp-translator/ompparser/src)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils/omp-translator)
endif()

set(ACCPARSER_GRAMMAR_TARGET_FILES
  acclexer.cpp
  accparser.cpp
)

add_custom_command(OUTPUT
    ${ACCPARSER_GRAMMAR_TARGET_FILES}
    COMMAND
    antlr4 ${ACCPARSER_GRAMMAR_FILES} -Werror -Dlanguage=Cpp -listener -visitor -o ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${ACCPARSER_GRAMMAR_FILES}"
    )

add_custom_target(accparser_grammar DEPENDS ${ACCPARSER_GRAMMAR_TARGET_FILES})

add_compile_options(-Wall)

# The accparser library for installation and distribution
add_library(accparser SHARED ${ACCIR_SOURCE_FILES} ${ACCPARSER_GRAMMAR_TARGET_FILES})
add_dependencies(accparser accparser_grammar)
target_link_libraries(accparser
    antlr4-runtime
    )
target_include_directories(accparser PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
target_include_directories(accparser SYSTEM PUBLIC
    /usr/include/antlr4-runtime
    )
if (USE_OMPPARSER)
    target_link_libraries(accparser
        ompparser
        )
    add_executable(omp_demo.out omp_demo.cpp)
    add_dependencies(omp_demo.out accparser)
    target_link_libraries(omp_demo.out
        accparser
        antlr4-runtime
        )
endif()

add_executable(acc_demo.out acc_demo.cpp)
add_dependencies(acc_demo.out accparser)
target_link_libraries(acc_demo.out
    accparser
    antlr4-runtime
    )

# Install headers and libraries
install(FILES
        src/OpenACCIR.h
        src/OpenACCKinds.h
        DESTINATION include)
install(TARGETS ${accparser_targets}
        LIBRARY DESTINATION lib
        )
