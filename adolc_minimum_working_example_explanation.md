# Understanding the minimum working example

This documents provides an step-by-step explanation of the [minimum working example](./adolc_minimum_working_example.md) that may be useful for ADOL-C newcomers.
We assume that we have already created the CMake project (and the corresponding `CMakeLists.txt` file) and now we want to write a small C++ program to compute the derivative of f(x)=e<sup>x</sup>  using ADOL-C.
The first step is to load the libraries used in our project, including (of course) ADOL-C:

	// Include libraries
	#include <iostream>
	#include <iomanip>
	#include <cmath>
	#include <adolc/adolc.h>

We can also use the `std` namespace to make our code less verbose:

	 // Define namespaces
	 using namespace std; 


Now we start the `main()` function of our project, which should look something like this:

		
	int main() {
	
		...
		
		// We will write our code here
		
		...
		
	    return 0;
	}

The first block of the `main()` function is the initialization of the active and passive variables that define the problem. 
Note that all active variables are initialized with the special ADOL-C type `adouble` and all passive variables are initialized with the usual type `double`.
All independent, intermediate, and dependent variables should be declared using the `adouble` type!

    // Initialize passive variables
    int m = 1, n = 1;
    auto xp = new double[n]; xp[0] = 1.;    // Independent vector
    auto yp = new double[m]; yp[0] = 0.;    // Dependent vector

    // Initialize active variables
    auto x = new adouble[n];
    auto y = new adouble[m];

After this we set a tag to indentify the trace that records all the arithmetic operations that will be differentiated:

    // Set the tag for the Automatic Differentiation trace
    int tag = 0;
    
 Now we start tracing all the arithmetic operations required to evaluate our function using the commands `trace_on(tag)` and `trace_off()`.
 Note that before performing any floating operation we have to load the value of the passive independent variables into their active counterparts using the `<<=` operator.
 Similarly we  have to unload the value of the independent active variables into their passive counterparts using the `>>=` operator.
 
     // Start tracing floating point operations
    trace_on(tag);  // Start of the active section

    // Assign independent variables
    x[0] <<= xp[0];

    // Evaluate the body of the differentiated code
    // In our case we want to evaluate the derivatives of f(x)=exp(x)
    y[0] = exp(x[0]);

    // Assign dependent variables
    y[0] >>= yp[0];

    trace_off();    // End of the active section


The next step is to define the tangent and derivative arrays and define the `keep` flag that could be used for a subsequent reverse differentiation.
In this example we set `keep=0` because we do not intend to do perform a differentiation in reverse mode.

    // Define the tangent vector
    auto x1 = new double[n]; x1[0] = 1;

    // Define the vector of first derivatives
    auto y1 = new double[m];

    // Define a flag to prepare for a reverse automatic differentiation
    int keep = 1;



Finally we can evaluate the derivative of our code by calling the `fos_forward()` function with the following arguments:
 
-  `tag` - AD trace identifier 
- `m` - Number of dependent variables 
- `n` -  Number of independent variables 
- `keep` - Flag for reverse differentiation 
-  `xp` - Array of independent variable values
- `x1` - Array of tangent direction 
- `yp` - Array of dependent variable values 
- `y1` -  Array of first derivatives 

and then print the AD and analytic derivative values on the screen using the `std::cout` stream:

    // Compute the derivatives of f(x)
    fos_forward(tag, m, n, keep, xp, x1, yp, y1);
    cout << "Derivative computation in forward mode" << endl;
    cout << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout.precision(8);
    cout.setf(ios::fixed);
    cout << setw(20) << y1[0] << setw(25) << exp(xp[0])<< endl;
    cout << endl;
 
 
If the execution of the program was successful you should be able to see this message on your screen:
 
	  Derivative computation in reverse mode
	       AD derivative      Analytic derivative
		      2.71828183               2.71828183
          
 


If you want to learn more about ADOL-C, the examples available at the [adolc_demos directory](./my_demos) may help you to get started and explore many of the features of the ADOL-C library!
