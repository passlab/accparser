#pragma acc parallel loop gang worker vector present (a, b, c, d) num_gangs (num_gangs) num_workers (32) vector_length (32)
#pragma acc kernels loop gang worker vector present (a, b, c, d) independent
#pragma acc update host (rsdnm)
#pragma acc update device (indxp, jndxp, np)
#pragma acc parallel loop gang present (rsd) num_gangs (nz-2) num_workers (num_workers) vector_length (32)
#pragma acc kernels loop gang present (rsd)
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang present (u, rsd) num_gangs (nz-2) num_workers (num_workers/2) vector_length (64)
#pragma acc kernels loop gang present (u, rsd)
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc update host (rsdnm)
