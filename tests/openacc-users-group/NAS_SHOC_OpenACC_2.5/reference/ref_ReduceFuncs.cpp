#pragma acc data copyin (idata[0:nItems])
#pragma acc kernels loop reduction (+: sum)
#pragma acc data copyin (idata[0:nItems])
#pragma acc kernels loop reduction (+: sum)
