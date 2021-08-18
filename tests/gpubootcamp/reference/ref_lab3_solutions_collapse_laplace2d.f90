!$acc parallel loop reduction (max: error) copyin (A) copyout (Anew) collapse (2)
!$acc parallel loop copyin (Anew) copyout (A) collapse (2)
