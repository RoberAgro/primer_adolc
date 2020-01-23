<script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>

# ADOL-C minimum working example


## Introduction

This decument describes how to set up and compile a small, yet complete, C++ project using ADOL-C to check if the installation was successful.

## Creating the CMake project

In this tutorial we will assume that we are building our C++ project using CMake. From wikipedia:

> CMake is a cross-platform free and open-source software tool for managing the build process of software using a compiler-independent method.

In order to compile a C++ project using CMake from a IDE (such as CLion or Visual Studio) we just need to write a small `CMakeLists.txt` file. In our case, this file should look something like this:


	# Set CMake version
	cmake_minimum_required(VERSION 3.14)

	# Set project name
	project(adolc_mwe)

	# Set path to header files directories
	include_directories("$ENV{ADOLC_INCLUDE}")

	# Set path to executable directories
	link_directories("$ENV{ADOLC_LIB}")

	# Add source files to compile to the project
	add_executable(PROJECT_NAME main.cpp)

	# Add external libraries
	target_link_libraries(PROJECT_NAME -ladolc)



Where the environmental variables `ADOLC_INCLUDE` and `ADOLC_LIB` point to the directories containing the ADOLC headers and executables, respectively.


## Defining the environmental variables
You can define the environmental variables used in the `CMakeLists.txt` file adding (something similar) to these lines to your `.bashrc` file:


	export ADOLC_INCLUDE="/home/robertoa/my_software/adolc-2.7.0/adolc_base/include"
	export ADOLC_LIB="/home/robertoa/my_software/adolc-2.7.0/adolc_base/lib64"


## Writing the C++ program

Now that we have prepared the `CMakeLists.txt` file of the project we can start using the ADOL-C library.

The code snippet below is a minimum working example showing how to compute the derivatives of the function $f(x)=e^{x}$ .
You should be able to compile this example straight ahead if the installation was successful.
Check out the [detailed explanation of the minimum working example](./adolc_minimum_working_example_explanation.md) if you want to learn more about how ADOL-C works. 


	// Include libraries
	#include <iostream>
	#include <iomanip>
	#include <cmath>
	#include <adolc/adolc.h>

	// Define namespaces
	using namespace std;

	// Define the function to be differentiated: f(x) = e^x
	adouble my_function(adouble x) {
	    adouble f = exp(x);
	    return f;
	};

	int main() {


	    // ----------------------------------------------------------------------- //
	    // Initialize problem variables
	    // ----------------------------------------------------------------------- //

	    // Initialize passive variables
	    int m = 1, n = 1;
	    auto xp = new double[n]; xp[0] = 1.;    // Independent vector
	    auto yp = new double[m]; yp[0] = 0.;    // Dependent vector

	    // Initialize active variables
	    auto x = new adouble[n];
	    auto y = new adouble[m];


	    // ----------------------------------------------------------------------- //
	    // Active section for automatic differentiation
	    // ----------------------------------------------------------------------- //

	    // Set the tag for the Automatic Differentiation trace
	    int tag = 0;

	    // Start tracing floating point operations
	    trace_on(tag);  // Start of the active section

	    // Assign independent variables
	    x[0] <<= xp[0];

	    // Evaluate the body of the differentiated code
	    y[0] = my_function(x[0]);

	    // Assign dependent variables
	    y[0] >>= yp[0];

	    trace_off();    // End of the active section


	    // ----------------------------------------------------------------------- //
	    // Compute the first derivative (forward mode)
	    // ----------------------------------------------------------------------- //

	    // Declare the tangent vector
	    auto x1 = new double[n]; x1[0] = 1;

	    // Declare the vector of first derivatives
	    auto y1 = new double[m];

	    // Define a flag to prepare for a reverse automatic differentiation or not
	    int keep = 0;

	    // Compute the derivatives of f(x)
	    fos_forward(tag, m, n, keep, xp, x1, yp, y1);
	    cout << "Derivative computation in forward mode" << endl;
	    cout << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
	    cout.precision(8);
	    cout.setf(ios::fixed);
	    cout << setw(20) << y1[0] << setw(25) << my_function(xp[0]).value() << endl;
	    cout << endl;

	    return 0;


	}
