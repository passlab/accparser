#pragma acc parallel loop reduction (max: error) copyin (A[:n*m]) copyout (Anew[:n*m]) collapse (2)
#pragma acc parallel loop copyin (Anew[:n*m]) copyout (A[:n*m]) collapse (2)
