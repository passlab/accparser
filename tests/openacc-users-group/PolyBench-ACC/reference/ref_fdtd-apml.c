#pragma acc data create (clf, tmp) copyin (Ax, Ry, Ex, Ey, Hz, czm, czp, cxmh, cxph, cymh, cyph) copyout (Bza, Ex, Ey, Hz)
#pragma acc parallel 
#pragma acc loop 
#pragma acc loop 
#pragma acc loop 
