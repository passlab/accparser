enable_testing()
add_custom_target(acc_gpubootcamp_test)

set(TEST_FILES
    lab1_laplace2d.kernels.f90
    lab1_solutions_laplace2d.kernels.c
    lab1_solutions_laplace2d.parallel.c
    lab1_solutions_laplace2d.parallel.f90
    # lab2_jacobi.f90
    lab2_laplace2d.c
    lab2_laplace2d.f90
    lab2_miniWeather_openacc.cpp
    lab2_miniWeather_openacc.f90
    lab2_solutions_jacobi.c
    lab2_solutions_laplace2d.c
    lab2_update_jacobi.c
    lab2_update_jacobi.f90
    lab2_update_laplace2d.c
    lab2_update_laplace2d.f90
    lab2_update_solution_jacobi.c
    # lab2_update_solution_jacobi.f90
    lab2_update_solution_laplace2d.c
    lab2_update_solution_laplace2d.f90
    lab3_collapse_jacobi.f90
    lab3_jacobi.c
    lab3_jacobi.f90
    lab3_laplace2d.c
    lab3_laplace2d.f90
    lab3_miniWeather_openacc.cpp
    lab3_miniWeather_openacc.f90
    lab3_solutions_collapse_jacobi.c
    # lab3_solutions_collapse_laplace2d.c
    lab3_solutions_collapse_laplace2d.f90
    lab3_solutions_tile_jacobi.c
    lab3_solutions_tile_laplace2d.c
    lab3_solutions_tile_laplace2d.f90
    lab3_tile_jacobi.f90
    lab4_miniWeather_openacc.cpp
    lab4_miniWeather_openacc.f90
    lab5_miniWeather_openacc.cpp
    lab5_miniWeather_openacc.f90
    # lan2_solutions_laplace2d.f90
    miniprofiler_miniWeather_openacc.f90
    miniprofiler_miniWeather_openacc_exr2.f90
    miniprofiler_miniWeather_openacc_exr3.f90
    miniprofiler_miniWeather_openacc_exr4.f90
    miniprofiler_miniWeather_openacc_exr5.f90
    rdf.cpp
    rdf.f90
    rdf_collapse.cpp
    rdf_data_directive.cpp
    # rdf_data_directive.f90
    rdf_gang.cpp
    rdf_gang_vector.cpp
    rdf_gang_vector_length.cpp
    rdf_gang_vector_worker.cpp
    rdf_kernel_directive.cpp
    rdf_kernel_directive.f90
    rdf_orig.f90
    rdf_parallel_directive.cpp
    rdf_parallel_directive.f90
    solution_rdf.cpp
    solutions_miniWeather_openacc.cpp
    solutions_miniWeather_openacc_exr2.cpp
    solutions_miniWeather_openacc_exr3.cpp
    solutions_miniWeather_openacc_exr4.cpp
    )

add_dependencies(acc_gpubootcamp_test acc_tester.out)

foreach(file_to_test ${TEST_FILES})
    add_test(
    NAME ${file_to_test}
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test.sh ${CMAKE_CURRENT_SOURCE_DIR}/${file_to_test} ${CMAKE_CURRENT_SOURCE_DIR}/reference/ref_${file_to_test}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()

