#pragma acc parallel loop reduction (max: error) copyin (A[:n*m]) copy (Anew[:n*m])
#pragma acc parallel loop copyin (Anew[:n*m]) copyout (A[:n*m])
