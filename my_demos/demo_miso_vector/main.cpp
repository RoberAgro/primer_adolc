// ------------------------------------------------------------------------------------------------------------------ //
// Example showing the differentiation a multiple-input single-output function
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


// Define the function to be differentiated: quadratic form f(x,y,z) = x^2 + z^2 + 2*x*y + z
adouble my_function(adouble * IN) {
    adouble x = IN[0], y = IN[1], z = IN[2];
    adouble f = x*x + z*z + 2*x*y + z;
    return f;
};


int main() {


    // -------------------------------------------------------------------------------------------------------------- //
    // Initialize problem variables
    // -------------------------------------------------------------------------------------------------------------- //

    // Initialize passive variables
    int m = 1, n = 3;
    auto xp = new double[n];    // Independent vector
    auto yp = new double[m];    // Dependent vector
    xp[0] = 1.00;
    xp[1] = 1.00;
    xp[2] = 1.00;

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
    x[1] <<= xp[1];
    x[2] <<= xp[2];

    // Add an artificial delay if desired by performing floating point operations that do not change the result
    // Note that sleep_for() or other waiting functions do not work when evaluating the ADOL-C trace
    for (int j = 0; j < 1e7; ++j) {x[0] = x[0] + 0*j;}

    // Evaluate the body of the differentiated code
    y[0] = my_function(x);

    // Assign dependent variables
    y[0] >>= yp[0];

    trace_off();    // End of the active section



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (forward vector mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Define the number of directions (same as the number of independent variables)
    int p = n;

    // Initialize the matrix of tangent directions (identity matrix)
    double **X = myalloc(n, p);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            if (i == j) { X[i][j] = 1.00; }
            else { X[i][j] = 0.00; }
        }
    }

    // Declare the matrix of first derivatives
    double **Y = myalloc(m, p);

    // Start timer
    auto t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(x, y, z)
    fov_forward(tag, m, n, p, xp, X, yp, Y);
    cout.precision(8);
    cout.setf(ios::fixed);
    cout << "Derivative computation using forward AD in vector mode" << endl;
    cout << setw(20) << "Component" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout << setw(20) << "dfdx" << setw(20) << Y[0][0] << setw(25) << 2*(xp[0]+xp[1]) << endl;
    cout << setw(20) << "dfdy" << setw(20) << Y[0][1] << setw(25) << 2*xp[0] << endl;
    cout << setw(20) << "dfdz" << setw(20) << Y[0][2] << setw(25) << 2*xp[2]+1 << endl;
    cout << endl;

    // Print elapsed time
    auto t_end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (reverse scalar mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Define the number of weight vectors (same as the number of independent variables)
    int q = m;

    // Declare the matrix of first derivatives (adjoint matrix)
    double **Z = myalloc(q, n);

    // Define the weight matrix
    double **U = myalloc(q, m);
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j) { U[i][j] = 1.00; }
            else { U[i][j] = 0.00; }
        }
    }

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Define a flag to prepare for a reverse automatic differentiation
    int keep = 1;
    zos_forward(tag, m, n, keep, xp, yp);

    // Compute the derivatives of f(x,y,z)
    fov_reverse(tag, m, n, q, U, Z);
    cout << "Derivative computation in reverse mode" << endl;
    cout << setw(20) << "dfdx" << setw(20) << Z[0][0] << setw(25) << 2*(xp[0]+xp[1]) << endl;
    cout << setw(20) << "dfdy" << setw(20) << Z[0][1] << setw(25) << 2*xp[0] << endl;
    cout << setw(20) << "dfdz" << setw(20) << Z[0][2] << setw(25) << 2*xp[2]+1 << endl;
    cout << endl;

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (gradient API)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare variables for the derivative computation
    auto grad = new double[n];

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the gradient of the scalar field
    gradient(tag, n, xp, grad);
    cout << "Derivative computation using the gradient API" << endl;
    cout << setw(20) << "dfdx" << setw(20) << grad[0] << setw(25) << 2*(xp[0]+xp[1]) << endl;
    cout << setw(20) << "dfdy" << setw(20) << grad[1] << setw(25) << 2*xp[0] << endl;
    cout << setw(20) << "dfdz" << setw(20) << grad[2] << setw(25) << 2*xp[2]+1 << endl;
    cout << endl;

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;


    return 0;


}
