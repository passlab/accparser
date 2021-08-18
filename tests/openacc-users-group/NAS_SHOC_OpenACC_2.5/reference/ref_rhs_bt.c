#pragma acc data present (forcing, rho_i, u, us, vs, ws, square, qs, rhs)
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector independent
#pragma acc parallel loop gang num_gangs (192) num_workers (16) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker independent
#pragma acc loop vector independent
