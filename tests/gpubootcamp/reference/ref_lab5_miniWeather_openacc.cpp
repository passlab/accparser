#pragma acc data copyin (state_tmp[(nz + 2 * hs) * (nx + 2 * hs) * NUM_VARS], hy_dens_cell[nz + 2 * hs], hy_dens_theta_cell[nz + 2 * hs], hy_dens_int[nz + 1], hy_dens_theta_int[nz + 1], hy_pressure_int[nz + 1]) create (flux[(nz + 1) * (nx + 1) * NUM_VARS], tend[nz * nx * NUM_VARS]) copy (state [0:(nz + 2 * hs) * (nx + 2 * hs) * NUM_VARS])
#pragma acc update host (state[(nz + 2 * hs) * (nx + 2 * hs) * NUM_VARS])
#pragma acc parallel loop collapse (3) private (inds, indt) default (present)
#pragma acc parallel loop collapse (2) private (ll, s, inds, stencil, vals, d3_vals, r, u, w, t, p) default (present)
#pragma acc parallel loop collapse (3) private (indt, indf1, indf2) default (present)
#pragma acc parallel loop collapse (2) private (ll, s, inds, stencil, vals, d3_vals, r, u, w, t, p) default (present)
#pragma acc parallel loop collapse (3) private (indt, indf1, indf2) default (present)
#pragma acc parallel loop collapse (2) default (present)
#pragma acc parallel loop private (x, xloc, mnt_deriv) default (present)
