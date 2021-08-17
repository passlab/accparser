enable_testing()
add_custom_target(acc_base_test)

set(TEST_FILES
    atomic.txt
    atomic_fortran.txt
    cache.txt
    cache_fortran.txt
    data.txt
    data_fortran.txt
    declare.txt
    declare_fortran.txt
    enter_data.txt
    enter_data_fortran.txt
    exit_data.txt
    exit_data_fortran.txt
    host_data.txt
    host_data_fortran.txt
    init.txt
    init_fortran.txt
    loop.txt
    loop_fortran.txt
    kernels.txt
    kernels_fortran.txt
    kernels_loop.txt
    kernels_loop_fortran.txt
    parallel.txt
    parallel_fortran.txt
    parallel_loop.txt
    parallel_loop_fortran.txt
    routine.txt
    routine_fortran.txt
    serial.txt
    serial_fortran.txt
    serial_loop.txt
    serial_loop_fortran.txt
    set.txt
    set_fortran.txt
    shutdown.txt
    shutdown_fortran.txt
    update.txt
    update_fortran.txt
    wait.txt
    wait_fortran.txt
    )

add_dependencies(acc_base_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

