#pragma acc data copyin (A[:m*n], Anew[:m*n])
#pragma acc update self (A[0:m*n])
