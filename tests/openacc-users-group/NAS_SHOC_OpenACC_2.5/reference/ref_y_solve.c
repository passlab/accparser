#pragma acc data present (rho_i, u, rhs, square, qs) create (lhsY, fjacY, njacY)
#pragma acc parallel loop gang num_gangs (jsize+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (jsize-1) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp22) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp02) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (gp22) num_workers (4) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
