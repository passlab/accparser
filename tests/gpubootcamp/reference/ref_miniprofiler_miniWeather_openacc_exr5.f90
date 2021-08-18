!$acc data copyin (state_tmp, hy_dens_cell, hy_dens_theta_cell, hy_dens_int, hy_dens_theta_int, hy_pressure_int) create (flux, tend) copy (state)
!$acc wait 
!$acc end data 
!$acc parallel loop collapse (3)
!$acc parallel loop gang
!$acc loop vector private (stencil, vals, d3_vals)
!$acc parallel loop collapse (3)
!$acc parallel loop gang
!$acc loop vector private (stencil, vals, d3_vals)
!$acc parallel loop collapse (3)
!$acc parallel loop collapse (2)
!$acc parallel loop 
!$acc parallel loop collapse (2) private (xloc, mnt_deriv, x)
