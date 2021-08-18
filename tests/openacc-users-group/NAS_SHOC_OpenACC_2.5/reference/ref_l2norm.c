#pragma acc data present (rsd, rsdnm)
#pragma acc parallel loop num_gangs (1) num_workers (1) vector_length (32)
#pragma acc kernels loop independent
#pragma acc parallel loop gang reduction (+: rsdnm0, rsdnm1, rsdnm2, rsdnm3, rsdnm4) num_gangs (nz0-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang reduction (+: rsdnm0, rsdnm1, rsdnm2, rsdnm3, rsdnm4)
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel num_gangs (1) num_workers (1) vector_length (1)
#pragma acc kernels 
#pragma acc parallel loop gang vector num_gangs (1) num_workers (1) vector_length (32)
#pragma acc kernels loop gang vector independent
