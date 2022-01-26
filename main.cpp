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
	
	airplane boeing(6.858, 6.86, 7.62, 35.05, 511, "747.tsv");
	boeing.print_debug();
}
