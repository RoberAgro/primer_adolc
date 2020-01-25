// ------------------------------------------------------------------------------------------------------------------ //
// Example showing the differentiation a single-input single-output function
//
// Author: Roberto Agromayor
// Date: January 2019
//
// ------------------------------------------------------------------------------------------------------------------ //


// Include libraries
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <adolc/adolc.h>


// Define namespaces
using namespace std;                // cout, endl
using namespace std::chrono;        // nanoseconds, system_clock, seconds


// Define the function to be differentiated: f(x) = e^x
adouble my_function(adouble x) {
    adouble f = exp(x);
    return f;
};


int main() {


    // -------------------------------------------------------------------------------------------------------------- //
    // Initialize problem variables
    // -------------------------------------------------------------------------------------------------------------- //

    // Initialize passive variables
    int m = 1, n = 1;
    auto xp = new double[n]; xp[0] = 1.;    // Independent vector
    auto yp = new double[m]; yp[0] = 0.;    // Dependent vector

    // Initialize active variables
    auto x = new adouble[n];
    auto y = new adouble[m];



    // -------------------------------------------------------------------------------------------------------------- //
    // Active section for automatic differentiation
    // -------------------------------------------------------------------------------------------------------------- //

    // Set the tag for the Automatic Differentiation trace
    int tag = 0;

    // Start tracing floating point operations
    trace_on(tag);  // Start of the active section

    // Assign independent variables
    x[0] <<= xp[0];

    // Add an artificial delay if desired by performing floating point operations that do not change the result
    // Note that sleep_for() or other waiting functions do not work when evaluating the ADOL-C trace
    for (int j = 0; j < 1e7; ++j) {x[0] = x[0] + 0*j;}

    // Evaluate the body of the differentiated code
    y[0] = my_function(x[0]);

    // Assign dependent variables
    y[0] >>= yp[0];

    trace_off();    // End of the active section



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (forward mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the tangent vector
    auto x1 = new double[n]; x1[0] = 1;

    // Declare the vector of first derivatives
    auto y1 = new double[m];

    // Define a flag to prepare for a reverse automatic differentiation
    int keep = 1;

    // Start timer
    auto t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(x)
    fos_forward(tag, m, n, keep, xp, x1, yp, y1);
    cout << "Derivative computation in forward mode" << endl;
    cout << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout.precision(8);
    cout.setf(ios::fixed);
    cout << setw(20) << y1[0] << setw(25) << my_function(xp[0]).value() << endl;
    cout << endl;

    // Print elapsed time
    auto t_end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (reverse mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the weight vector
    auto u = new double[m]; u[0] = 1;

    // Declare the vector of first derivatives (adjoint vector)
    auto z = new double[n];

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(x)
    fos_reverse(tag, m, n, u, z);
    cout << "Derivative computation in reverse mode" << endl;
    cout << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout << setw(20) << z[0] << setw(25) << my_function(xp[0]).value() << endl;
    cout << endl;

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;
    cout << endl;


    return 0;


}
