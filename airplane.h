#include <string>

extern "C" {

#include "glider_math.h"

}

class airplane {
private:
	double bodysurfacearea = 0.0;
	double wingsurfacearea = 0.0;
	double tailsurfacearea = 0.0;
	double radius = 0;
	int numEntries = 0;
	double *alpha, *x, *y, *stddev;
	std::string name;
	double span_efficiency_factor_e = 0.9;
	double oswalds_efficiency_number_e0;
	void calcBodyShape(double r, double l1, double l2, double l3);
	double two_d_coefficient_lift_vs_alpha_slope;
	double three_d_coefficient_lift_vs_alpha_slope;
	double skinFrictionCoefficient;

	void readPoints();
	void calcTailShape(double root_chord, double tail_chord, double height);

	double aspect_ratio = 1.0;
	double zero_lift_alpha;
	double *coefficient_of_lift;
	double *wingDragPolar;
	double *DragPolar;
	
public:
	airplane(double r, double l1, double l2, double l3, double area, double ar, double sfc, double tr, double tt, double th, std::string file);
	~airplane();
	void print_debug();
	void print_data();
};
