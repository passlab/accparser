#pragma acc parallel loop reduction (max: error) copyin (A[:n*m]) copyout (Anew[:n*m]) tile (32, 4)
#pragma acc parallel loop copyin (Anew[:n*m]) copyout (A[:n*m]) tile (32, 4)
