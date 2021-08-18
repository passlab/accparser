#pragma acc data present (flux_G, rho_i, frct, qs, rsd, u, utmp_G, rtmp_G)
#pragma acc parallel loop gang num_gangs (nz) num_workers (8) vector_length (128)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers2) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers2) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers2) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers4) vector_length (128)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (num_workers2) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers3) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (num_workers2) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
