#include "midpoint.hpp" // To use our library
#include "writer.hpp"   // This is the output function to write to file

// We store our results in a vector
#include <vector>

// On some platforms we need to add this in order
// to get M_PI defined
#define _USE_MATH_DEFINES

// for our usual math functions and constants
#include <math.h>

// For printing to the terminal
#include <iostream>

double f(double x)
{
    return sin(M_PI * x);
}

int main(int, char **)
{
    // (write your solution here)
    constexpr unsigned int max_iter{12}; // highest power of 2 we will compute

    /// limits
    ///  a: lower bound
    ///  b: upper boud
    constexpr double a = 0.2;
    constexpr double b = 1.3;

    /// Exact value of the integral
    const double I = (std::cos(M_PI * a) - std::cos(M_PI * b)) / M_PI; 
    // if this were c++26, I could let the compiler do this (constexpr)

    std::vector<int> ns;
    std::vector<double> values;

    for (int i{4}; i < max_iter; ++i)
    {
        int n = 0b1 << i;
        ns.push_back(n);
        values.push_back(fabs(midpoint_rule(a, b, n, f) - I));
    }

    writeToFile("series0_1_d_numbers.txt", ns);
    writeToFile("series0_1_d_errors.txt", values);

    std::cout << "Sucess" << std::endl;

    return 0;
}
