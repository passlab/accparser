#pragma acc data create (a, b, c, d, flux_G, indxp, jndxp, np, rho_i, frct, qs, rsd, u, tmat, tv, utmp_G, rtmp_G) copyout (rsdnm)
#pragma acc update device (u)
#pragma acc update device (u)
#pragma acc update host (u)
