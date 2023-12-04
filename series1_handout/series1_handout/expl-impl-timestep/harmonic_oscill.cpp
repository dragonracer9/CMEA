#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>
#include <iostream>
#include "writer.hpp"
#include <assert.h>

/// Uses the explicit Euler method to compute y from time 0 to time T
/// where y is a 2x1 vector solving the linear system of ODEs as in the exercise
///
/// @param[out] yT at the end of the call, this will have vNext
/// @param[in] y0 the initial conditions
/// @param[in] zeta the damping factor (see exercise)
/// @param[in] dt the step size
/// @param[in] T the final time at which to compute the solution.
///
/// The first component of y (the position) will be stored to y1, the second component (the velocity) to y2. The i-th entry of y1 (resp. y2) will contain the first (resp. second) component of y at time i*dt.
///

//----------------explicitEulerBegin----------------
void explicitEuler(std::vector<double> &y1, std::vector<double> &y2, std::vector<double> &time,
				   const Eigen::Vector2d &y0,
				   double zeta, double dt, double T)
{
	y1.clear();
	y2.clear();
	time.clear();
	y1.push_back(y0[0]);
	y2.push_back(y0[1]);
	time.push_back(0);

	const uint32_t n = (int)(T / dt);

	Eigen::Matrix2d A;							  // creating the A matrix
	A << 0, 1, -1, -2 * zeta;					  // initializing to the values previously calculated
	Eigen::Matrix2d M;							  // simplifying consecutive addition and multiplication into one operation (if i simply do y_tmp + A *y_tmp, the error scales to 1e7 very quickly, somehow this works far better)
	M = Eigen::MatrixXd::Identity(2, 2) + dt * A; // eigen documentation is terrible

	Eigen::Vector2d y_tmp; // I need a Eigen vector so that i can preform the matrix-vector multiplication
	y_tmp << y0[0], y0[1]; // setting initial values for y_tmp

	for (uint32_t i = 1; i <= n; ++i)
	{
		y_tmp = M * y_tmp;
		y1.push_back(y_tmp[0]); // not exactly the fastest way of adding onto the vector as it might have to reallocate to create space,
		y2.push_back(y_tmp[1]); // but i dont want the hassle of initializing to n zeros (not that is less work than writing this comment in which i complain about that)
		std::cout << y_tmp[0] << ',' << y_tmp[1] << std::endl;
		time.push_back(i * dt);
	}
	std::cout << time.back() << std::endl;
	std::cout << "size:" << y1.size() << ',' << y2.size() << std::endl;
	std::cout << "explicit done -------------------" << std::endl;
}
//----------------explicitEulerEnd----------------

// Implements the implicit Euler. Analogous to explicit Euler, same input and output parameters
//----------------implicitEulerBegin----------------
void implicitEuler(std::vector<double> &y1, std::vector<double> &y2, std::vector<double> &time,
				   const Eigen::Vector2d &y0,
				   double zeta, double dt, double T)
{
	// (write your solution here)
	// by implicit euler, i am assuming that you mean backward euler, since this is the terma that makes most sense in this context
	y1.clear();
	y2.clear();
	time.clear();
	y1.push_back(y0[0]);
	y2.push_back(y0[1]);
	time.push_back(0);

	const uint32_t n = (int)(T / dt);

	Eigen::Matrix2d A;							  // creating the A matrix
	A << 0, 1, -1, -2 * zeta;					  // initializing to the values previously calculated
	Eigen::Matrix2d M;							  // this is a matrix summarising the addition of y_{n+1} with dt * A * y_{n+1}
	M = Eigen::MatrixXd::Identity(2, 2) - dt * A; // calculating the M matrix such that i can then solve  M y_{n+1} = y_n

	Eigen::Vector2d y_tmp; // I need a Eigen vector so that i can preform the matrix-vector multiplication
	y_tmp << y0[0], y0[1]; // setting initial values for y_tmp

	for (uint32_t i = 1; i <= n; ++i)
	{
		y_tmp = M.lu().solve(y_tmp);
		y1.push_back(y_tmp[0]);
		y2.push_back(y_tmp[1]);
		std::cout << y_tmp[0] << ',' << y_tmp[1] << std::endl;
		time.push_back(i * dt);
	}
	std::cout << time.back() << std::endl;
	std::cout << "size:" << y1.size() << ',' << y2.size() << std::endl;
	std::cout << "implicit done -------------------" << std::endl;
}
//----------------implicitEulerEnd----------------

//----------------energyBegin----------------
// Energy computation given the velocity. Assume the energy vector to be already initialized with the correct size.
void Energy(const std::vector<double> &v, std::vector<double> &energy)
{
	assert(v.size() == energy.size());
	// (write your solution here)
	for (int i = 0; i < v.size(); ++i)
	{
		energy.at(i) = 0.5 * v.at(i) * v.at(i);
	}
}
//----------------energyEnd----------------

int main()
{

	double T = 20.0;
	double dt = 0.1; // Change this for explicit / implicit time stepping comparison
	const Eigen::Vector2d y0(1, 0);
	double zeta = 0.2;
	std::vector<double> y1;
	std::vector<double> y2;
	std::vector<double> time;
	explicitEuler(y1, y2, time, y0, zeta, dt, T);
	writeToFile("position_expl.txt", y1);
	writeToFile("velocity_expl.txt", y2);
	writeToFile("time_expl.txt", time);
	std::vector<double> energy(y2.size());
	Energy(y2, energy);
	writeToFile("energy_expl.txt", energy);
	y1.assign(y1.size(), 0);
	y2.assign(y2.size(), 0);
	time.assign(time.size(), 0);
	energy.assign(energy.size(), 0);
	implicitEuler(y1, y2, time, y0, zeta, dt, T);
	writeToFile("position_impl.txt", y1);
	writeToFile("velocity_impl.txt", y2);
	writeToFile("time_impl.txt", time);
	Energy(y2, energy);
	writeToFile("energy_impl.txt", energy);

	return 0;
}
