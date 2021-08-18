#pragma acc data copyin (ce) present (flux_G, frct, rsd)
#pragma acc parallel loop gang num_gangs (nz) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (nz-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (jend-jst+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
