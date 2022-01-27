#include "nrutil.h"

/*
 * Fit float data to Linear Regression in form y = a + bx;
 *
 * Given a set of data points x[1..ndata], y[1..ndata] with individual standard deviations
 * sig[1..ndata], fit them to a straight line y = a + bx by minimizing X^2. Returned are a,
 * b and their respective probable uncertainties siga and sigb, the chi-square chi2, and the
 * goodness-of-fit probability q (that the fit would have X^2 this large or larger). If
 * mwt = 0 on input, then the standard deviations are assumed to be unavailable: q is returned
 * as 1.0 and the normalization of chi2 is to unit standard deviation on all points.
 *
 * Copied from (with slight modification): NUMERICAL RECIPES IN C, THE ART OF SCIENTIFIC
 * COMPUTING, SECOND EDITION, by William H. Press, Saul A. Teukolsky, William T. Vetterling,
 * and Brian P. Flannery. Copyright 1992, reprinted with corrections in 1995.
 *
 * Software version: 2.06
 *
*/


void fit(double x[], double y[], int ndata, double sig[], int mwt, double *a, double *b, double *siga, double *sigb, double *chi2, double *q);


/*
 * Returns the incomplete gamma funciton Q(a,x) = 1-P(a,x);
 *
 * Same information as above regarding function origin
 * Page 218
 *
*/

double gammq(double a, double x);

/*
 * Returns the incomplete gamma function P(a,x) evaluated by its series representation as
 * gamser.
 * Also returns ln gamma(alpha) as gln.
 *
*/

void gser(double *gamser, double a, double x, double *gln);

/*
 * Returns the incomplete gamma function Q(a,x) evaluated by its conitnued fraction
 * representation as gammcf. Also returns ln gamma(alpha) as gln.
 *
 * Same information as above regarding function origin
 * Page 219
 *
*/

void gcf(double *gammcf, double a, double x, double *gln);

/*
 * Returns the value ln [ gamma(xx)] for xx > 0
 *
 * Same information as above regarding function origin
 * Page 214
 *
*/

double gammln(double xx);

/*
 * Using the Newton_Raphson method, find the root of a function known to lie in the interval
 * [x1, x2]. The root rtnewt will be refined until its accuracy is known within +- xacc.
 * funcd is a user-supplied routine that returns both the function value and the first
 * derivative of the function at the point x.
 *
 * This function has been modified to only calculate linear roots
 *
 * Same information as above regarding function origin
 * Page 365
 *
*/

double rtnewt(double m, double b, double x1, double x2, double xacc);

/*
 * Find Minimum Value in an Array and return Index
 *  
 * This function is not from NUMERICAL RECIPES IN C
 *
*/

unsigned find_min(double *arr, unsigned numEntries);
