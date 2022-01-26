#include <string>

class airplane {
private:
	double bodysurfacearea = 0;
	double wingsurfacearea = 0;
	double radius = 0;
	int numEntries = 0;
	double *alpha, *x, *y;
	std::string name;
	double span_efficiency_factor_e = 0.9;
	void calcBodyShape(double r, double l1, double l2, double l3);
	double two_d_coefficient_lift_vs_alpha;
	void readPoints();
public:
	airplane(double r, double l1, double l2, double l3, double area, std::string file);
	~airplane();
	void print_debug();
	void print_data();
};
