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
