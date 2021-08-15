enable_testing()
add_custom_target(acc_test)

set(TEST_FILES
    atomic.txt
    data.txt
    declare.txt
    enter_data.txt
    exit_data.txt
    host_data.txt
    init.txt
    loop.txt
    kernels.txt
    parallel.txt
    parallel_loop.txt
    routine.txt
    serial.txt
    set.txt
    shutdown.txt
    update.txt
    )

add_dependencies(acc_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

