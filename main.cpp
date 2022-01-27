#include <iostream>
#include "airplane.h"

int main() {
	// Boeing 747-200
	//
	// Radius: 22.5', 6.86 m
	// Length1: 25',  7.62 m
	// Length2: 115', 35.05 m
	// Length3: 85', 25.91 m
	// Wing Area: 5500 ft^2, 511 m^2
	// Aspect Ratio: 7
	// Skin Friction Coefficient: 0.0030
	// Tail Root Chord: 45', 13.72 m
	// Tail Tip Chord: 12.5', 3.81 m
	// Tail Height: 7.75', 2.362 m
	
	std::cout << "Boeing 747-200\n";
	airplane boeing(6.858, 6.86, 7.62, 35.05, 511, 7.0, 0.0030, 13.72, 3.81, 2.362, "747.tsv");
	boeing.print_debug();

	std::cout << "\n\n===============================================\n\n";

	// Tempest CFD
	//
	// Radius: 0.08 m
	// Length1: 0.45 m
	// Length2: 0.23 m
	// Length3: 0.88 m
	// Wing Area: 0.63 m^2
	// Aspect Ratio: 16.5
	// Skin Friction Coefficient 0.0055
	// Tail Root Chord: 0.27 m
	// Tail Tip Chord: 0.13 m
	// Tail Height: 0.4 m
	
	std::cout << "Tempest CFD\n";
	airplane tempest(0.08, 0.45, 0.23, 0.88, 0.63, 16.5, 0.0055, 0.27, 0.13, 0.4, "tempest.tsv");
	tempest.print_debug();
}
