#pragma acc parallel loop collapse (3) private (inds, indt)
#pragma acc parallel loop collapse (2) private (ll, s, inds, stencil, vals, d3_vals, r, u, w, t, p)
#pragma acc parallel loop collapse (3) private (indt, indf1, indf2)
#pragma acc parallel loop collapse (2) private (ll, s, inds, stencil, vals, d3_vals, r, u, w, t, p)
#pragma acc parallel loop collapse (3) private (indt, indf1, indf2)
#pragma acc parallel loop collapse (2)
#pragma acc parallel loop private (x, xloc, mnt_deriv)
