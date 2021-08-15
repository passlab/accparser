enable_testing()
add_subdirectory(base)
add_subdirectory(gpubootcamp)
add_subdirectory(openacc-users-group)

add_compile_options(-Wall)

add_executable(acc_tester.out
    acc_tester.cpp
    preprocess.cpp)
add_dependencies(acc_tester.out accparser)
target_link_libraries(acc_tester.out
    accparser
    antlr4-runtime
    )

set(accparser_targets accparser)
set(executable_targets
    acc_tester.out
    )

install(TARGETS ${executable_targets}
        RUNTIME DESTINATION bin
        )
