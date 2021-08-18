#pragma acc data copyout (y) copyin (A, x) create (tmp)
#pragma acc parallel present (tmp, A, x) num_gangs (nx/100) num_workers (100)
#pragma acc loop gang worker
#pragma acc loop seq
#pragma acc parallel present (y, tmp, A) num_gangs (ny/100) num_workers (100)
#pragma acc loop gang worker
#pragma acc loop seq
