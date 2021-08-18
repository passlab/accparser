enable_testing()
add_custom_target(acc_nas_test)

set(TEST_FILES
    add_bt.c
    add_sp.c
    adi.c
    # blts.c //token recognition error at: '/'
    bt.c
    # buts.c //token recognition error at: '/'
    calcnp.c
    # cg.c //token recognition error at: '/'
    # ep.c //token recognition error at: '/'
    erhs.c
    error_bt.c
    error_sp.c
    exact_rhs.c
    # ft.c //token recognition error at: '/'
    initialize.c
    # jacld.c //token recognition error at: '/'
    # jacu.c //token recognition error at: '/'
    l2norm.c
    lu.c
    # MDFuncs.cpp //token recognition error at: ']'
    mg.c
    ReduceFuncs.cpp
    rhs_bt.c
    rhs_lu.c
    rhs_sp.c
    sp.c
    ssor.c
    StencilFuncs.cpp
    txinvr.c
    x_solve.c
    y_solve.c
    z_solve.c
    )

add_dependencies(acc_nas_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

