enable_testing()
add_custom_target(acc_polybench_test)

set(TEST_FILES
    # 2mm.c // unknown syntax of using num_workers/num_gangs
    # 3mm.c // the same as 2mm.c, e.g. num_workers[0](8)
    adi.c
    )

add_dependencies(acc_polybench_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

