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
#include <adolc/adtl.h>             // Header for traceless ADOL-C!


// Define namespaces
using namespace std;                // cout, endl
using namespace std::chrono;        // nanoseconds, system_clock, seconds


// Use special traceless namespace to define adoubles
typedef adtl::adouble adouble;



// Define the function to be differentiated: f(x) = e^[(x0+x1+...+xn)/n]
adouble my_function(adouble * IN, const int n) {
    adouble sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += IN[i];
    }
    adouble f = exp(sum/n);
    return f;
};

double my_function(const double * IN, const int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += IN[i];
    }
    double f = exp(sum/n);
    return f;
};


int main() {


    // -------------------------------------------------------------------------------------------------------------- //
    // Initialize problem variables
    // -------------------------------------------------------------------------------------------------------------- //

    // Set the desired number of independent variables
    const int n = 10;

    // Initialize passive variables
    auto grad = new double[n];
    auto xp = new double[n];
    for (int i = 0; i < n; ++i) {
        xp[i] = 1.00;
    }

    // Initialize active variables
    adouble f = 0.0;
    auto x = new adouble[n];
    for (int i = 0; i < n; ++i) {
        x[i].setValue(xp[i]);
    }

    // Initialize the seed variables
    double seedOne = 1.0, seedZero = 0.0;


    // -------------------------------------------------------------------------------------------------------------- //
    // Compute the gradient vector
    // -------------------------------------------------------------------------------------------------------------- //

    // Compute each component in scalar mode (for-loop)
    for (int i = 0; i < n; ++i) {

        // Seed the independent variables one at a time
        for (int j = 0; j < n; ++j) {
            if (i == j ) {
                x[j].setADValue(&seedOne);
            } else {
                x[j].setADValue(&seedZero);
            }
        }

        // Evaluate the function
        f = my_function(x, n);

        // Evaluate the function derivatives. Remember to dereference the pointer returned by getADValue()!
        grad[i] = *(f.getADValue());

    }

    // Print the results
    cout.precision(8);
    cout.setf(ios::fixed);
    cout << "Derivative computation in forward mode" << endl;
    cout << setw(20) << "Direction" << setw(20) << "AD derivative" << setw(25) << "Analytic derivative" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(20) << i+1 << setw(20) << grad[i] << setw(25) << my_function(xp, n)/n << endl;
    }
    cout << endl;

    return 0;


}


