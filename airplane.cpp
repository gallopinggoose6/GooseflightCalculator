#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "airplane.h"

airplane::airplane(double r, double l1, double l2, double l3, double area, double ar, double sfc, double tr, double tt, double th, std::string file) {
	calcBodyShape(r, l1, l2, l3);
	calcTailShape(tr, tt, th);
	wingsurfacearea = area;
	name = file;
	aspect_ratio = ar;
	skinFrictionCoefficient = sfc;
	readPoints();

	double b = 0.0;
	double sigb = 0.0, sigm = 0.0, chi2 = 0.0, q = 0.0;	// discarded for now

	// Find Wing Drag Polar
	fit(alpha, x, numEntries, stddev, 0, &b, &two_d_coefficient_lift_vs_alpha_slope, &sigb, &sigm, &chi2, &q);
	three_d_coefficient_lift_vs_alpha_slope = two_d_coefficient_lift_vs_alpha_slope / (1.0 + (57.3 * two_d_coefficient_lift_vs_alpha_slope) / (M_PI * span_efficiency_factor_e * aspect_ratio));
	zero_lift_alpha = rtnewt(two_d_coefficient_lift_vs_alpha_slope, b, alpha[0], alpha[numEntries - 1], 0.001);
	coefficient_of_lift = new double[numEntries];
	for (unsigned i = 0; i < numEntries; ++i) {
		coefficient_of_lift[i] = three_d_coefficient_lift_vs_alpha_slope * (alpha[i] - zero_lift_alpha);	
	}

	wingDragPolar = new double[numEntries];
	for (unsigned i = 0; i < numEntries; ++i) {
		wingDragPolar[i] = y[i] + (coefficient_of_lift[i] * coefficient_of_lift[i]) / (M_PI * span_efficiency_factor_e * aspect_ratio);
	}

	// Whole Aircraft Drag Polar
	
	double Swet = 2 * wingsurfacearea + bodysurfacearea + tailsurfacearea;

	double skinFrictionDrag = skinFrictionCoefficient * Swet / wingsurfacearea;
	
	std::cout << "skin friction drag: " << skinFrictionDrag << "\n";

	// Oswalds Efficiency Number

	// U.S. Navy, Raymers subsonic approximation
	oswalds_efficiency_number_e0 = 1.78 * (1.0 - 0.045 * pow(aspect_ratio, 0.68)) - 0.64;
	
	// Obert Flight Testing approximation LESS ACCURATE
	// oswalds_efficiency_number_e0 = 1.0 / (1.05 + 0.007 * M_PI * aspect_ratio);
	std::cout << "oswalds: " << oswalds_efficiency_number_e0 << '\n';

	int minIndex = find_min(wingDragPolar, numEntries);
	double k = 1.0 / (M_PI * oswalds_efficiency_number_e0 * aspect_ratio);
	std::cout << "k1: " << k << "\n";

	std::cout << "coefficient of lift at min drag: " << coefficient_of_lift[minIndex] << '\n';

	double parasiteDrag = skinFrictionDrag + k * coefficient_of_lift[minIndex]*coefficient_of_lift[minIndex]; // Assume that the minimum drag occurs at minimum Lift
	
	std::cout << "parasite drag: " << parasiteDrag << '\n';

	double k2 = -2*k*coefficient_of_lift[minIndex];
	
	DragPolar = new double[numEntries];
	for (unsigned i = 0; i < numEntries; ++i) {
		DragPolar[i] = parasiteDrag + k * coefficient_of_lift[i] * coefficient_of_lift[i] + k2 * coefficient_of_lift[i];
	}
}

airplane::~airplane() {
	delete[] x;
	delete[] y;
	delete[] alpha;
	delete[] stddev;
	delete[] coefficient_of_lift;
	delete[] wingDragPolar;
	delete[] DragPolar;
}

void airplane::calcTailShape(double root_chord, double tail_chord, double height) {
	tailsurfacearea = height * (root_chord + tail_chord) / 2.0;
}

void airplane::calcBodyShape(double r, double l1, double l2, double l3) {
	// Get Surface Area of Body Cylinder
	
	double SA_body = 2*r*M_PI*l2;

	// Get Surface Area of Nose, assuming perfect cone
	
	double SA_nose = M_PI*r*sqrt(l1*l1+r*r);

	// Get Surface Area of Tail - Assume Cone
	
	double SA_tail = 2*r*M_PI*l3;

	bodysurfacearea = SA_body + SA_nose + SA_tail;
}

void airplane::readPoints() {
	std::ifstream input(name);
	std::string line;
	if (input.is_open()) {
		numEntries = 0;
		while (getline(input, line)) ++numEntries;
		input.clear();
		input.seekg(0);
		x = new double[numEntries];
		y = new double[numEntries];
		stddev = new double[numEntries];
		for (int i = 0; i < numEntries; ++i) stddev[i] = 0.0;
		alpha = new double[numEntries];
		unsigned counter = 0;
		while (getline(input, line)) {
			std::vector<std::string> split;
			std::string accum = "";
			for (int i = 0; i < line.size(); ++i) {
				if (line[i] == '\t') {
					split.push_back(accum);
					accum = "";
				}
				else accum += line[i];
			}
			split.push_back(accum);
			alpha[counter] = std::stod(split[0]);
			x[counter] = std::stod(split[1]);
			y[counter] = std::stod(split[2]);
			++counter;
		}
		input.close();
	} else {
		std::cout << "ERROR\n";
		exit(1);
	}
}

void airplane::print_data() {

}

void airplane::print_debug() {
	std::cout << "two d lift coefficient slope: " << two_d_coefficient_lift_vs_alpha_slope << std::endl;
	std::cout << "angle of zero lift: " << zero_lift_alpha << std::endl;
	std::cout << std::endl;

	for (unsigned i = 0; i < numEntries; ++i) {
		std::cout << alpha[i] << '\t' << coefficient_of_lift[i] << '\t' << DragPolar[i] << '\n';
	}
}
