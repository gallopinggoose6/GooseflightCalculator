Gooseflight Calculator

The purpose of this program is to model the flight of basically anything: Geese, Boeing 747s, The Caspian Sea Monster, that paper airplane you made in 2nd grade, the belly flop of a starship as it doesn't die on Mars on impact. Anything.

As this is a massive undertaking this program is very much a work in progress. Currently it models the Drag Polar on just about any aircraft with an error of 20% to 30%. More features will come and accuracy will improve.

To build this program, all that is required is a C and a C++ Compiler, as well as CMake. In a terminal navigate to this repository and type "cmake ." and a project will be made. If you are on a UNIX based system all that should be required is the program make, and a makefile will be generated. The next step is to type "make" in the terminal and the program should build. If on Windows, CMake will make a Visual Studio project (provided that you have it installed). The program can then be built from within Visual Studio.

This program borrows code from "Numerical Recipes in C, Second Edition", and at some point it will probably start using Catch2 for tests.
