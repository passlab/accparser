#pragma acc data copy (h_g2 [0:nbin]) copyin (h_x [0:nconf * numatm], h_z [0:nconf * numatm], h_y [0:nconf * numatm])
#pragma acc routine seq
#pragma acc parallel loop default (present)
#pragma acc atomic 
