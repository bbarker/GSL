#include <config.h>
#include <math.h>
#include <gsl_math.h>
#include <gsl_rng.h>
#include <gsl_randist.h>
#include <gsl_sf_erf.h>

double
gsl_ran_gaussian_tail (const gsl_rng * r, const double a, const double sigma)
{
  /* Returns a gaussian random variable larger than s
   * This implementation does one-tailed deviates.
   * FIXME: what to do about a < 0?
   */

  double s = a / sigma;

  if (s < 1)
    {
      /* For small s, use a direct rejection method. The limit s < 1
         can be adjusted to optimise the overall efficiency */

      double x;

      do
	{
	  x = fabs (gsl_ran_gaussian (r, 1.0));
	}
      while (x < s);
      return x * sigma;
    }
  else
    {
      /* Use the "supertail" deviates from the last two steps
       * of Marsaglia's rectangle-wedge-tail method, as described
       * in Knuth, v2, 3rd ed, pp 123-128.  (See also exercise 11, p139,
       * and the solution, p586.)
       */

      double u, v, x;

      do
	{
	  u = gsl_rng_uniform (r);
	  do
	    {
	      v = gsl_rng_uniform (r);
	    }
	  while (v == 0.0);
	  x = sqrt (s * s - 2 * log (v));
	}
      while (x * u > s);
      return x * sigma;
    }
}

double
gsl_ran_gaussian_tail_pdf (const double x, const double a, const double sigma)
{
  if (x < a)
    {
      return 0;
    }
  else
    {
      double N, p;
      double u = x / sigma ;

      gsl_sf_result f;
      gsl_sf_erfc_impl (a / (sqrt (2.0) * sigma), &f);

      N = 0.5 * f.val;

      p = (1 / (N * sqrt (2 * M_PI) * sigma)) * exp (-u * u / 2);

      return p;
    }
}

double
gsl_ran_ugaussian_tail (const gsl_rng * r, const double a)
{
  return gsl_ran_gaussian_tail (r, a, 1.0) ;
}

double
gsl_ran_ugaussian_tail_pdf (const double x, const double a)
{
  return gsl_ran_gaussian_tail_pdf (x, a, 1.0) ;
}
