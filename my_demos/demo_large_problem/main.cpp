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


// Define the function to be differentiated: f(x) = e^[(x0+x1+...+xn)/n]
adouble my_function(adouble * x, int n) {
    adouble sum;
    for (int i = 0; i < n; ++i) {
        sum += x[i];
    }
    adouble f = exp(sum/n);
    return f;
};

double my_function(const double * x, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += x[i];
    }
    double f = exp(sum/n);
    return f;
};


int main() {


    // -------------------------------------------------------------------------------------------------------------- //
    // Initialize problem variables
    // -------------------------------------------------------------------------------------------------------------- //

    // Initialize passive variables
    int m = 1, n = 50;          // Set n equal to the desired number of independent variables
    auto xp = new double[n];    // Independent vector
    auto yp = new double[m];    // Dependent vector

    // Set the value of the independent variables
    for (int i = 0; i < n; ++i) {
        xp[i] = 1.;
    }

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
    for (int i = 0; i < n; ++i) {
        x[i] <<= xp[i];
    }

    // Add an artificial delay if desired by performing floating point operations that do not change the result
    // Note that sleep_for() or other waiting functions do not work when evaluating the ADOL-C trace
    for (int j = 0; j < 1e7; ++j) {x[0] = x[0] + 0*j;}

    // Evaluate the body of the differentiated code
    y[0] = my_function(x, n);

    // Assign dependent variables
    y[0] >>= yp[0];

    trace_off();    // End of the active section



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative using forward AD in scalar mode
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the tangent vector
    auto x1 = new double[n];

    // Declare the vector of first derivatives
    auto y1 = new double[m];

    // Define a flag to prepare for a reverse automatic differentiation or not
    int keep = 0;

    // Start timer
    auto t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(x)
    cout << "Derivative computation using forward AD in scalar mode" << endl;
    cout << setw(20) << "Direction" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout.precision(8);
    cout.setf(ios::fixed);

    for (int i = 0; i < n; ++i) {

        // Get the current direction x1 = (0, 0, ..., 1, ..., 0, 0)
        for (int j = 0; j < n; ++j) {
            if (i == j) { x1[j] = 1.00; }
            else { x1[j] = 0.00; }}

        // Compute the derivative along the current direction (scalar mode)
        fos_forward(tag, m, n, keep, xp, x1, yp, y1);

        // Print the derivative value
        cout << setw(20) << i+1 << setw(20) << y1[0] << setw(25) << my_function(xp, n)/n << endl;

    }

    // Print elapsed time
    auto t_end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative using forward AD in vector mode
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

    // Initialize matrix of first derivatives
    double **Y = myalloc(m, p);

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives along all directions (vector mode)
    cout << "Derivative computation using forward AD in vector mode" << endl;
    cout << setw(20) << "Direction" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    fov_forward(tag, m, n, p, xp, X, yp, Y);
    for (int i = 0; i < p; ++i) {
        cout << setw(20) << i+1 << setw(20) << Y[0][i] << setw(25) << my_function(xp, n)/n << endl;
    }

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative using reverse AD
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare variables for the derivative computation
    auto u = new double[m];   // Weight vector
    auto z = new double[n];   // Adjoint vector
    u[0] = 1;

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(x)
    keep = 1;
    zos_forward(tag, m, n, keep, xp, yp);
    fos_reverse(tag, m, n, u, z);
    cout << "Derivative computation using reverse AD" << endl;
    cout << setw(20) << "Direction" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(20) << i+1 << setw(20) << z[i] << setw(25) << my_function(xp, n)/n << endl;
    }

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;
    cout << endl;



    /* Observations:
     *
     *  Running in forward scalar mode the computational time depends linearly on the number of variables :(
     *  Running in forward vector mode requires less computational time but also scales with the number of variables :(
     *  Running in reverse mode the computational time is independent on the number of variables! :)
     *
     * */

    return 0;


}
