!$acc parallel loop reduction (max: error) copyin (A) copyout (Anew)
!$acc parallel loop copyin (Anew) copyout (A)
