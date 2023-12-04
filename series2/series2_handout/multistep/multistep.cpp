#include <writer.hpp>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>
#include <iostream>
#include <cmath>

///
/// Computes N iterations of Adam-Bashforth 2
/// @param[out] y will contain the values of y (not y'!) at
///             the end. should have length N+1
/// @param[out] time will contain the times at the end, should have length N+1
/// @param[in] T the end time
/// @param[in] N the number of iterations to perform
/// @param[in] y0 the initial y value y(0)
/// @param[in] dydt0 the initial value y'(0)
///
//----------------AB2Begin----------------
void adamBashforth2(std::vector<double> &y, std::vector<double> &time,
                    double T, int N, double y0, double dydt0)
{
    const double dt = T / N;

    Eigen::Matrix2d A; // creating the A matrix
    A << 0, 1, -6, -5;
    // First compute u_1 using FE
    Eigen::Vector2d u(y0, dydt0);
    Eigen::Vector2d u1 = u + dt * A * u;

    y.at(0) = y0;
    y.at(1) = u1[0];
    time.at(0) = 0;
    time.at(1) = dt;
    // Compute Adam-Bashforth for u_2, u_3, ...
    // (write your solution here)
    for (int i{2}; i <= N; ++i)
    {
        Eigen::Vector2d tmp = u1 + (dt / 2) * (-(A * u) + 3 * A * u1);
        u = u1;
        u1 = tmp;
        // u_n+2 = u_n+1 + dt / 2 (-f(u_n) +3 f(u_n+1))
        y.at(i) = tmp[0]; // not exactly the fastest way of adding onto the vector as it might have to reallocate to create space,
        std::cout << u1[0] << ',' << u1[1] << std::endl;
        time.at(i) = i * dt;
    }
}
//----------------AB2End----------------

double exactSolution(double t)
{
    // (write your solution here)
    return 5.0 * std::exp(-2 * t) - 4 * std::exp(-3 * t);
}

int main(int, char **)
{
    double T = 1;

    std::vector<double> errors;
    std::vector<double> resolutions;
    double error = 0;
    for (int k = 5; k <= 12; ++k)
    {
        int N = 1 << k;
        std::vector<double> y(N + 1);
        std::vector<double> time(N + 1, 0);

        double y0 = 1;
        double dydt0 = 2;

        adamBashforth2(y, time, T, N, y0, dydt0);

        // Compute error
        error = std::abs(exactSolution(T) - y.back());
        // (write your solution here)
        errors.push_back(error);
        resolutions.push_back(N);

        if (k == 12)
        {
            writeToFile("y.txt", y);
            writeToFile("time.txt", time);
        }
    }
    writeToFile("errors_ab2.txt", errors);
    writeToFile("resolutions.txt", resolutions);
}
