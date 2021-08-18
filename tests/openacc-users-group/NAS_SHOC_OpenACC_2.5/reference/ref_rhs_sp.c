#pragma acc data present (rho_i, u, qs, square, speed, rhs, forcing, us, vs, ws)
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (gp2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2-4) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
