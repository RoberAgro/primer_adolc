// ------------------------------------------------------------------------------------------------------------------ //
// Example showing the differentiation a multiple-input multiple-output function
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


// Radius of the sphere
static double R = 2.00;


// Define the function to be differentiated: parametric helix r(t) = [R*cos(t), R*sin(t), t]
adouble * my_function(adouble * IN) {
    adouble u = IN[0];
    adouble v = IN[1];
    auto f = new adouble[3];
    f[0] = R*cos(u)*cos(v);
    f[1] = R*sin(u)*cos(v);
    f[2] = R*sin(v);
    return f;
}


int main() {

    // -------------------------------------------------------------------------------------------------------------- //
    // Initialize problem variables
    // -------------------------------------------------------------------------------------------------------------- //

    // Parameter values
    double u = 0.50, v = 0.25;

    // Initialize passive variables
    int m = 3, n = 2;
    auto xp = new double[n];    // Independent vector
    auto yp = new double[m];    // Dependent vector
    xp[0] = u;
    xp[1] = v;

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

    // Add an artificial delay if desired by performing floating point operations that do not change the result
    // Note that sleep_for() or other waiting functions do not work when evaluating the ADOL-C trace
    for (int j = 0; j < 1e7; ++j) {x[0] = x[0] + 0*j;}

    // Evaluate the body of the differentiated code
    auto temp = my_function(x);
    y[0] = temp[0];
    y[1] = temp[1];
    y[2] = temp[2];

    // Assign dependent variables
    y[0] >>= yp[0];
    y[1] >>= yp[1];
    y[2] >>= yp[2];

    trace_off();    // End of the active section



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (forward scalar mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the tangent vector
    auto x1 = new double[n];

    // Declare the vector of first derivatives
    auto y1 = new double[m];

    // Define a flag to prepare for a reverse automatic differentiation
    int keep = 1;

    // Start timer
    auto t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(u,v)
    cout << "Derivative computation in forward mode" << endl;
    cout << setw(20) << "Component" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout.precision(8);
    cout.setf(ios::fixed);

    // Partial derivatives with respect to u
    x1[0] = 1.0; x1[1] = 0.0;
    fos_forward(tag, m, n, keep, xp, x1, yp, y1);
    cout << setw(20) << "dxdu" << setw(20) << y1[0] << setw(25) << -R*sin(u)*cos(v) << endl;
    cout << setw(20) << "dydu" << setw(20) << y1[1] << setw(25) << +R*cos(u)*cos(v) << endl;
    cout << setw(20) << "dzdu" << setw(20) << y1[2] << setw(25) << 0.00 << endl;

    // Partial derivatives with respect to v
    x1[0] = 0.0; x1[1] = 1.0;
    fos_forward(tag, m, n, keep, xp, x1, yp, y1);
    cout << setw(20) << "dxdv" << setw(20) << y1[0] << setw(25) << -R*cos(u)*sin(v) << endl;
    cout << setw(20) << "dydv" << setw(20) << y1[1] << setw(25) << -R*sin(u)*sin(v) << endl;
    cout << setw(20) << "dzdv" << setw(20) << y1[2] << setw(25) << +R*cos(v)<< endl;
    cout << endl;

    // Print elapsed time
    auto t_end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (reverse scalar mode)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the weight vector
    auto U = new double[m];

    // Declare the vector of first derivatives (adjoint vector)
    auto z = new double[n];

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(u,v)
    cout << "Derivative computation in reverse mode" << endl;
    cout << setw(20) << "Component" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;

    // Partial derivatives of x(u,v)
    U[0] = 1; U[1] = 0; U[2] = 0;
    fos_reverse(tag, m, n, U, z);
    cout << setw(20) << "dxdu" << setw(20) << z[0] << setw(25) << -R*sin(u)*cos(v) << endl;
    cout << setw(20) << "dxdv" << setw(20) << z[1] << setw(25) << -R*cos(u)*sin(v) << endl;

    // Partial derivatives of y(u,v)
    U[0] = 0; U[1] = 1; U[2] = 0;
    fos_reverse(tag, m, n, U, z);
    cout << setw(20) << "dydu" << setw(20) << z[0] << setw(25) << +R*cos(u)*cos(v) << endl;
    cout << setw(20) << "dydv" << setw(20) << z[1] << setw(25) << -R*sin(u)*sin(v) << endl;

    // Partial derivatives of z(u,v)
    U[0] = 0; U[1] = 0; U[2] = 1;
    fos_reverse(tag, m, n, U, z);
    cout << setw(20) << "dzdu" << setw(20) << z[0] << setw(25) << 0.00 << endl;
    cout << setw(20) << "dzdv" << setw(20) << z[1] << setw(25) << +R*cos(v) << endl;

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;



    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the first derivative (Jacobian API)
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the Jacobian matrix
    auto jac = myalloc(m,n);

    // Start timer
    t_start = std::chrono::high_resolution_clock::now();

    // Compute the derivatives of f(u,v)
    jacobian(tag, m, n, xp, jac);

    // Compare the AD and the analytic derivatives
    cout << "Derivative computation using the Jacobian API" << endl;
    cout << setw(20) << "Component" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    cout << setw(20) << "dxdu" << setw(20) << jac[0][0] << setw(25) << -R*sin(u)*cos(v) << endl;
    cout << setw(20) << "dxdv" << setw(20) << jac[0][1] << setw(25) << -R*cos(u)*sin(v) << endl;
    cout << setw(20) << "dydu" << setw(20) << jac[1][0] << setw(25) << +R*cos(u)*cos(v) << endl;
    cout << setw(20) << "dydv" << setw(20) << jac[1][1] << setw(25) << -R*sin(u)*sin(v) << endl;
    cout << setw(20) << "dzdu" << setw(20) << jac[2][0] << setw(25) << 0.00 << endl;
    cout << setw(20) << "dzdv" << setw(20) << jac[2][1] << setw(25) << +R*cos(v) << endl;

    // Print elapsed time
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = std::chrono::duration<double>(t_end - t_start).count();
    cout << "The elapsed time was " << elapsed_seconds*1000 << " milliseconds" << endl;
    cout << endl << endl;


    return 0;


}


