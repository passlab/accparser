#pragma acc parallel present (rhs) num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels present (rhs)
#pragma acc loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel present (rhs) num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels present (rhs)
#pragma acc loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel present (us, vs, ws, qs, u, speed, rhs) num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels present (us, vs, ws, qs, u, speed, rhs)
#pragma acc loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc data present (rho_i, us, speed, rhs) create (lhsX, lhspX, lhsmX, rhonX, rhsX)
#pragma acc parallel loop gang num_gangs (nz2+1) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc data present (rho_i, vs, speed, rhs) create (lhsY, lhspY, lhsmY, rhoqY)
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (nz2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (gp2-2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc data present (rho_i, ws, speed, rhs) create (lhsZ, lhspZ, lhsmZ, rhosZ)
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker
#pragma acc loop vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
#pragma acc parallel loop gang num_gangs (ny2) num_workers (8) vector_length (32)
#pragma acc kernels loop gang
#pragma acc loop worker vector
