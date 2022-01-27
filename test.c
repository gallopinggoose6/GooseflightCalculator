#include <stdio.h>
#include <stdlib.h>
#include "glider_math.h"

int main() {
	{
	double x[] = { -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0 };
	double y[] = { -0.3505, -0.2514, -0.1493, -0.0318, 0.0912, 0.2133, 0.3048, 0.318, 0.3925, 0.4889, 0.5855, 0.6808, 0.7744, 0.8721, 0.9729, 1.061, 1.1263 };
	double standarddevs[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

	double b = 0.0;
	double m = 0.0;

	int ndata = 16;

	int mwt = 0;

	double sigb = 0.0;
	double sigm = 0.0;

	double chi2 = 0.0;
	double q = 0.0;

	fit(x, y, ndata, standarddevs, mwt, &b, &m, &sigb, &sigm, &chi2, &q);

	printf("b is equal to:\t%f\n", b);
	printf("m is equal to:\t%f\n", m);
	printf("sigb is equal to:\t%f\n", sigb);
	printf("sigm is equal to:\t%f\n", sigm);
	printf("chi2 is equal to:\t%f\n", chi2);
	printf("q is equal to:\t%f\n", q);
	}

	printf("\n\n======================================\n\n");

	{
        double x[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
        double y[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
        double standarddevs[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

        double b = 0.0;
        double m = 0.0;

        int ndata = 6;

        int mwt = 0;

        double sigb = 0.0;
        double sigm = 0.0;

        double chi2 = 0.0;
        double q = 0.0;

        fit(x, y, ndata, standarddevs, mwt, &b, &m, &sigb, &sigm, &chi2, &q);

        printf("b is equal to:\t%f\n", b);
        printf("m is equal to:\t%f\n", m);
        printf("sigb is equal to:\t%f\n", sigb);
        printf("sigm is equal to:\t%f\n", sigm);
        printf("chi2 is equal to:\t%f\n", chi2);
        printf("q is equal to:\t%f\n", q);
        }
}
