/** @file primordial.h Documented includes for primordial module */

#include "transfer.h"

#ifndef __PRIMORDIAL__
#define __PRIMORDIAL__

enum primordial_spectrum_type {
  smooth_Pk,
  inflation_V,
  inflation_H
};

/**
 * All tables of transfer functions \f$ \Delta_l^{X} (k) \f$.
 *
 * Once initialized by transfer_init(), contains all tables of
 * transfer functions used for interpolation in other modules, for all
 * requested modes (scalar/vector/tensor), initial conditions, type
 * (temperature, polarization, etc), l and k.
 */
struct primordial {

  enum primordial_spectrum_type primordial_spec_type;

  double k_pivot; /* pivot scale in Mpc-1 */

  double A_s_ad;  /* scalar amplitude (adiabatic) */
  double n_s_ad;  /* scalar tilt (adiabatic) */
  double alpha_s_ad; /* scalar running (adiabatic) */

  double * lnk; /* list of ln(k) values lnk[index_k] */
  int lnk_size; /* number of ln(k) values */

  double ** lnpk; /* primordial spectra (lnP[index_mode])[index_ic][index_k] */
  double ** ddlnpk; /* second derivative of lnP for spline interpolation */
  int * ic_size;  /* number of initial conditions ic_size[index_x] */
  int md_size; /* number of modes (scalars, tensors...)*/

  /** @name - flag regulating the amount of information sent to standard output (none if set to zero) */

  //@{

  short primordial_verbose;

  //@}

  ErrorMsg error_message; /**< zone for writing error messages */
};

/*************************************************************************************************************/

/*
 * Boilerplate for C++ 
 */
#ifdef __cplusplus
extern "C" {
#endif

  int primordial_spectrum_at_k(
			      int index_mode,
			      double k,
			      double * pk
			      );

  int primordial_init(
		    struct perturbs * ppt_input,
		    struct precision * ppr_input,
		    struct primordial * ppm_output
		    );
    
  int primordial_free();
    
  int primordial_get_lnk_list_size(
				   double kmin,
				   double kmax,
				   double k_per_decade,
				   int * lnk_list_size
				   );

  int primordial_get_lnk_list(
			      double kmin,
			      double k_per_decade,
			      int lnk_list_size,
			      double * lnpk_list
			      );

#ifdef __cplusplus
}
#endif

/**  
 * @name Constants
 */

//@{


//@}

#endif