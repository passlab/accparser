#pragma acc data copyin (A, B, x) create (tmp) copyout (y)
#pragma acc parallel 
#pragma acc loop 
#pragma acc loop 
