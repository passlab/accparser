#pragma acc parallel present (rhs, u) num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels present (rhs, u)
#pragma acc loop gang
#pragma acc loop worker
#pragma acc loop vector
