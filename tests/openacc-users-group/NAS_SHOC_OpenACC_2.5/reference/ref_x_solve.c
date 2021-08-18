#pragma acc data present (rho_i, u, qs, rhs, square) create (lhsX, fjacX, njacX)
#pragma acc parallel loop gang num_gangs (isize+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (isize-1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp12) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
