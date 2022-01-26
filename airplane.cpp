#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "airplane.h"

airplane::airplane(double r, double l1, double l2, double l3, double area, std::string file) {
	calcBodyShape(r, l1, l2, l3);
	wingsurfacearea = area;
	name = file;
	readPoints();
}

airplane::~airplane() {
	delete[] x;
	delete[] y;
	delete[] alpha;
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
	for (unsigned i = 0; i < numEntries; ++i) {
		std::cout << alpha[i] << '\t' <<  x[i] << '\t' << y[i] << '\n';
	}
}
