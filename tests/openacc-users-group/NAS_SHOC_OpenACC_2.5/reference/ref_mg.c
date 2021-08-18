#pragma acc data create (u[0:gnr], v[0:gnr], r[0:gnr])
#pragma acc data deviceptr (r1, r2) present (ou[0:n3*n2*n1], or[0:n3*n2*n1])
#pragma acc parallel loop gang num_gangs (n3-2) num_workers (16) vector_length (64)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (n3-2) num_workers (16) vector_length (64)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc data deviceptr (u1, u2) present (ou[0:n3*n2*n1], ov[0:n3*n2*n1], or[0:n3*n2*n1])
#pragma acc parallel num_gangs (n3-2) num_workers (8) vector_length (128)
#pragma acc kernels 
#pragma acc loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel num_gangs (n3-2) num_workers (8) vector_length (128)
#pragma acc kernels 
#pragma acc loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc data deviceptr (x1, y1) present (or[0:m3k*m2k*m1k], os[0:m3j*m2j*m1j])
#pragma acc parallel loop gang num_gangs (m3j-2) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (m3j-2) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc data deviceptr (z1, z2, z3) present (oz[0:mm3*mm2*mm1], ou[0:n3*n2*n1])
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-d3) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-d3) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-d3) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-d3) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (mm3-1) num_workers (8) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc data copyin (or[0:n3*n2*n1])
#pragma acc parallel loop gang reduction (+: s) reduction (max: temp) num_gangs (n3-2) num_workers (8) vector_length (128)
#pragma acc kernels loop gang reduction (+: s) reduction (max: temp) independent
#pragma acc loop worker independent
#pragma acc loop vector independent
#pragma acc data present (ou[0:n3*n2*n1])
#pragma acc parallel loop gang num_gangs (n3-2) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (n3-2) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop vector independent
#pragma acc parallel loop gang num_gangs (n2) vector_length (128)
#pragma acc kernels loop gang independent
#pragma acc loop vector independent
#pragma acc update device (oz[0:n3*n2*n1])
#pragma acc parallel present (oz[0:n3*n2*n1]) num_gangs (n3) num_workers (8) vector_length (128)
#pragma acc kernels present (oz[0:n3*n2*n1])
#pragma acc loop gang independent
#pragma acc loop worker independent
#pragma acc loop vector independent
