#include "glider_math.h"
#include <math.h>
#include <float.h>

#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

void fit(double x[], double y[], int ndata, double sig[], int mwt, double *a, double *b, double *siga, double *sigb, double *chi2, double *q) {
	int i;
	double wt,t,sxoss,sx=0.0,sy=0.0,st2=0.0,ss,sigdat;

	*b=0.0;
	if (mwt) {
		ss=0.0;
		for (i = 1; i <= ndata; ++i) {
			wt = 1.0/SQR(sig[i]);
			ss += wt;
			sx += x[i] * wt;
			sy += y[i] * wt;
		}
	} else {
		for (i = 1; i <= ndata; ++i) {
			sx += x[i];
			sy += y[i];
		}
		ss = ndata;
	}
	sxoss = sx / ss;
	if (mwt) {
		for (i = 1; i <= ndata; ++i) {
			t = (x[i] - sxoss) / sig[i];
			st2 += t*t;
			*b += t * y[i] / sig[i];
		}
	} else {
		for (i = 1; i <= ndata; ++i) {
			t = x[i] - sxoss;
			st2 += t * t;
			*b += t * y[i];
		}
	}
	*b /= st2;
	*a = (sy - sx * (*b)) / ss;
	*siga = sqrt((1.0 + sx * sx / (ss * st2)) / ss);
	*sigb = sqrt(1.0 / st2);

	*chi2 = 0.0;

	if (mwt == 0) {
		for (i = 1; i <= ndata; ++i) *chi2 += SQR(y[i] - (*a) - (*b) * x[i]);
		*q = 1.0;
		sigdat = sqrt((*chi2)/(ndata - 2));
		*siga *= sigdat;
		*sigb *= sigdat;
	} else {
		for (i = 1; i <= ndata; ++i) *chi2 += SQR((y[i] - (*a) - (*b) * x[i])/sig[i]);
		*q = gammq(0.5 * (ndata - 2), 0.5 * (*chi2));
	}
}

double gammq(double a, double x) {
	double gamser, gammcf, gln;

	if (x < 0.0 || a <= 0.0) nrerror("Invalid arguments in routine gammq");
	if (x < (a+1.0)) {
		gser(&gamser, a, x, &gln);
		return 1.0-gamser;
	} else {
		gcf(&gammcf, a, x, &gln);
		return gammcf;
	}
}

void gser(double *gamser, double a, double x, double *gln) {
	int n;
	float sum,del,ap;

	*gln=gammln(a);
	if (x <= 0.0 ) {
		if (x < 0.0) nrerror("x less than - in routine gser");
		*gamser = 0.0;
		return;
	} else {
		ap = a;
		del = sum = 1.0/a;
		for (n = 1; n <= ITMAX; n++) {
			++ap;
			del *= x/ap;
			sum += del;
			if (fabs(del) < fabs(sum)*EPS) {
				*gamser = sum * exp(-x + a * log(x) - (*gln));
				return;
			}
		}
		nrerror("a too large, ITMAX too small in routine gser");
		return;
	}
}

void gcf(double *gammcf, double a, double x, double *gln)
{
	int i;
	double an,b,c,d,del,h;

	*gln=gammln(a);
	b = x+1.0-a;
	c = 1.0/FPMIN;
	d = 1.0/b;
	h = d;
	for (i = 1; i <= ITMAX; ++i) {
		an = -i * (i-a);
		b += 2.0;
		d = an * d + b;
		if (fabs(d) < FPMIN) d = FPMIN;
		c = b + an/c;
		if (fabs(c) < FPMIN) c = FPMIN;
		d = 1.0/d;
		del = d*c;
		h *= del;
		if (fabs(del - 1.0) < EPS) break;
	}
	if (i > ITMAX) nrerror("a too large, ITMAX too small in gcf");
	*gammcf = exp(-x + a * log(x) - (*gln)) * h;
}

double gammln(double xx)
{
	double x, y, tmp, ser;
	static double cof[6] = {76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5 };
	int j;

	y = x = xx;
	tmp = x + 5.5;
	tmp -= (x + 0.5) * log(tmp);
	ser = 1.000000000190015;
	for (j = 0; j <= 5; ++j) ser += cof[j]/++y;
	return -tmp+log(2.5066282746310005*ser/x);
}

#define JMAX 100

double rtnewt(double m, double b, double x1, double x2, double xacc)
{
	int j;
	double dx, f, rtn;

	rtn = 0.5 * (x1 + x2);
	for (j = 1; j <= JMAX; ++j) {
		f = rtn * m + b;
		dx = f / m;
		rtn -= dx;
		if ((x1-rtn)*(rtn-x2) < 0.0) nrerror("Jumped out of brackets in rtnewt");
		if (fabs(dx) < xacc) return rtn;
	}
	nrerror("Maximum number of iterations exceeded in rtnewt");
	return 0.0;
}

unsigned find_min(double *arr, unsigned numEntries) {
	double min = DBL_MAX;
	unsigned index = 0;
	for (unsigned i = 0; i < numEntries; ++i) {
		if (arr[i] < min) {
			index = i;
			min = arr[i];
		}
	}
	return index;
}
