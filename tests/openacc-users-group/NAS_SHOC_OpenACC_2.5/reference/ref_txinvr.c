#pragma acc parallel present (rho_i, us, vs, ws, rhs, speed, qs) num_gangs (nz2) num_workers (16) vector_length (32)
#pragma acc kernels present (rho_i, us, vs, ws, rhs, speed, qs)
#pragma acc loop gang
#pragma acc loop worker
#pragma acc loop vector
