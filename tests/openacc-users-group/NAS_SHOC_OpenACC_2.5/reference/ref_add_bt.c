#pragma acc parallel loop gang present (u, rhs) num_gangs (gp22) num_workers (4) vector_length (32)
#pragma acc kernels loop gang present (u, rhs)
#pragma acc loop worker independent
#pragma acc loop vector independent
