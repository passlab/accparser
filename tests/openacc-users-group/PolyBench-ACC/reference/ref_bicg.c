#pragma acc data copyout (s, q) copyin (A, r, p)
#pragma acc parallel present (q, A, p) num_gangs (nx/100) num_workers (100)
#pragma acc loop gang worker
#pragma acc loop seq
#pragma acc parallel present (s, r, A) num_gangs (ny/100) num_workers (100)
#pragma acc loop gang worker
#pragma acc loop seq
