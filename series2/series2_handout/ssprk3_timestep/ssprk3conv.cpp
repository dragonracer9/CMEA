#include <vector>
#include <iostream>
#include <cmath>
#include "writer.hpp"

double soln_exact(double t, double u0)
{
    return (t + u0) * std::exp(-2 * t);
}

double f(double t, double u)
{
    // (write your solution here)
    return std::exp(-2 * t) - 2 * u;
}

/// Uses the SSP RK3 method to compute u from time 0 to time T
/// for the ODE $u'=e^{-2t}-2u$
///
/// @param[out] u at the end of the call (solution at all time steps)
/// @param[out] time contains the time levels
/// @param[in] u0 the initial data
/// @param[in] dt the step size
/// @param[in] T the final time up to which to compute the solution.
///

//----------------SSPRK3Begin----------------
void SSPRK3(std::vector<double> &u, std::vector<double> &time,
            const double &u0, double dt, double T)
{
    const unsigned int nsteps = std::round(T / dt);
    u.clear();
    time.clear();
    u.resize(nsteps + 1);
    time.resize(nsteps + 1);

    // Write your SSPRK3 code here
    // (write your solution here)
    u.at(0) = u0;
    time.at(0) = 0;

    for (size_t i{}; i < nsteps; ++i)
    {
        time.at(i + 1) = (i + 1) * dt;

        double y1 = u.at(i);
        double c1 = f(time.at(i), y1);

        double y2 = y1 + dt * c1;
        double c2 = f(time.at(i + 1), y2);

        double y3 = y1 + (dt / 4) * (c1 + c2);

        u.at(i + 1) = y1 + dt * ((1 / 6.0) * (c1 + f(time.at(i + 1), y2)) + 2 / 3.0 * f(time.at(i) + 0.5 * dt, y3));
        //std::cout << time.at(i) << "    " << y1 << ", " << y2 << ", " << y3 << " and u[" << i << "] = " << u.at(i) << std::endl;
    }
    std::cout << time.back() << " where the last u is " << u.back() << std::endl;
    std::cout << nsteps << std::endl;
    std::cout << "explicit done -------------------" << std::endl;
}
//----------------SSPRK3End----------------

int main(int argc, char **argv)
{

    double T = 10.0;

    std::vector<double> dts = std::vector<double>(8);
    std::vector<double> errors = std::vector<double>(8);

    // To make some plotting easier, we take the dt parameter in as an optional
    // parameter.

    const double u0 = 0.;
    std::vector<double> time;
    std::vector<double> u;
    for (int i{}; i < 8; ++i)
    {
        dts.at(i) = std::pow(0.5, i);
        SSPRK3(u, time, u0, dts.at(i), T);
        double u_sol = soln_exact(T, u0);
        errors.at(i) = std::abs(u.back() - u_sol);
    }
    writeToFile("dt.txt", u);
    writeToFile("error.txt", time);

    return 0;
}
