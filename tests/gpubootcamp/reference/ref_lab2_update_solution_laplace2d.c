#pragma acc parallel loop copy (A[:m*n], Anew[:m*n])
#pragma acc loop 
#pragma acc parallel loop copy (A[:m*n], Anew[:m*n])
#pragma acc loop 
