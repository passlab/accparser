!$acc parallel loop reduction (max: error) copyin (A) copyout (Anew) tile (32, 4)
!$acc parallel loop copyin (Anew) copyout (A) tile (32, 4)
