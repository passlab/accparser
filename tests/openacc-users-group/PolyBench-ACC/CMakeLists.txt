enable_testing()
add_custom_target(acc_polybench_test)

set(TEST_FILES
    # 2mm.c // unknown syntax of using num_workers/num_gangs
    # 3mm.c // the same as 2mm.c, e.g. num_workers[0](8)
    adi.c
    atax.c
    bicg.c
    cholesky.c
    convolution-2d.c
    convolution-3d.c
    correlation.c
    covariance.c
    doitgen.c
    durbin.c
    dynprog.c
    fdtd-2d.c
    fdtd-apml.c
    floyd-warshall.c
    gemm.c
    gemver.c
    gesummv.c
    gramschmidt.c
    jacobi-1d-imper.c
    jacobi-2d-imper.c
    lu.c
    ludcmp.c
    mvt.c
    reg_detect.c
    seidel-2d.c
    symm.c
    syr2k.c
    syrk.c
    trisolv.c
    trmm.c
    )

add_dependencies(acc_polybench_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

