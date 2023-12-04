#include <writer.hpp>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>
#include <iostream>
#include <cmath>

///
/// Computes N iterations of Forward-Euler.
/// @param[out] y will contain the values of y (not y'!) at
///             the end. should have length N+1
/// @param[out] time will contain the times at the end, should have length N+1
/// @param[in] T the end time
/// @param[in] N the number of iterations to perform
/// @param[in] y0 the initial y value y(0)
/// @param[in] dydt0 the initial value y'(0)
///
//----------------FEBegin----------------
void forwardEuler(std::vector<double> &y, std::vector<double> &time,
                  double T, int N, double y0, double dydt0)
{
    const double dt = T / N;
    // (write your solution here)
    std::cout << "dt: " << dt << std::endl;

    y.at(0) = y0;
    time.at(0) = 0;

    // u' =  A * u
    Eigen::Vector2d ytmp(y0, dydt0);

    Eigen::Matrix2d A; // creating the A matrix
    A << 0, 1, -6, -5;
    // initializing to the values previously calculated
    Eigen::Matrix2d M;
    M = Eigen::MatrixXd::Identity(2, 2) + dt * A; // eigen documentation is terrible

    for (int i = 1; i <= N; ++i)
    {
        ytmp = M * ytmp;
        y.at(i) = ytmp[0];
        std::cout << ytmp[0] << ',' << ytmp[1] << std::endl;
        time.at(i) = i * dt;
    }
    std::cout << time.back() << std::endl;
    std::cout << "size:" << y.size() << std::endl;
    std::cout << "bashford done -------------------" << std::endl;
}
//----------------FEEnd----------------

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

        forwardEuler(y, time, T, N, y0, dydt0);

        // Compute error
        // for (size_t i{}; i < time.size(); ++i)
        //     error += std::abs(exactSolution(time[i]) - y[i]); // see, i was under the impression we were not to take the final one step erroe, but the total error
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
    writeToFile("errors.txt", errors);
    writeToFile("resolutions.txt", resolutions);
}
