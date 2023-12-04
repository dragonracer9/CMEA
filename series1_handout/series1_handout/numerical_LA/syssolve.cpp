#include <iostream>
#include <Eigen/Dense>
#include <chrono>

///
/// Solve linear system Ax=b by computing inv(A)*b
/// @param[in] A is an NxN Eigen::MatrixXd
/// @param[in] b is an N Eigen::VectorXd
/// @return    x which approximately solves Ax=b
///
//----------------SolveInverseBegin----------------
Eigen::VectorXd solve_inverse(Eigen::MatrixXd A, Eigen::VectorXd b)
{
  Eigen::VectorXd solution;
  // std::cout << A << '\n'
  //           << b << std::endl;
  auto begin = std::chrono::high_resolution_clock::now();

  // (write your solution here)
  solution = A.inverse() * b;

  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  std::cout << "Time elapsed, inverse solver (ms): " << time / 1e6 << std::endl;

  // std::cout << solution << std::endl;
  return solution;
}
//----------------SolveInverseEnd----------------

///
/// Solve linear system Ax=b using an LU solver
/// @param[in] A is an NxN Eigen::MatrixXd
/// @param[in] b is an N Eigen::VectorXd
/// @return    x which approximately solves Ax=b
///
//----------------SolveLUBegin----------------
Eigen::VectorXd solve_lu(Eigen::MatrixXd A, Eigen::VectorXd b)
{
  Eigen::VectorXd solution;
  auto begin = std::chrono::high_resolution_clock::now();

  // (write your solution here)
  solution = A.lu().solve(b); // composition is nice

  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  std::cout << "Time elapsed, LU solver (ms): " << time / 1e6 << std::endl;
  return solution;
}
//----------------SolveLUEnd----------------

int main(int argc, char **argv)
{
  int N = 10;
  if (argc > 1)
  {
    // Read N from command line
    // We use atof because we want to allow things like 1e7
    N = int(atof(argv[1]));
  }

  // Construct Hilbert's matrix
  Eigen::MatrixXd H(N, N);
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      H(i, j) = 1. / (1 + i + j);
    }
  }

  // Declare Eigen vector type for doubles
  using vector_t = Eigen::VectorXd;

  // Create right hand side for the equation
  vector_t rhs(N);
  rhs.setOnes();

  //----------------UseInverseBegin----------------
  // Use solve_inverse to compute the solution, and find the residual
  // (write your solution here)
  vector_t sol_inv(N);
  sol_inv = solve_inverse(H, rhs);
  vector_t Residual = rhs - (H * sol_inv);

  double norm_R = Residual.norm();
  double norm_en = std::sqrt(N); // since the vector consists of only ones, it's norm is simply the square root of the number of elements

  double relative_norm = norm_R / norm_en;

  std::cout << "\n\nTesting the solution: A*sol=\n" /*final newline is necessary due to the formatting of the output of the vector*/ << H * sol_inv << "\n\n"
            << relative_norm << "\nDoes it match?" << std::endl;
  //----------------UseInverseEnd----------------

  //----------------UseLUBegin----------------
  // Use solve_lu to compute the solution, and find the residual
  // (write your solution here)
  auto sol_lu = solve_lu(H, rhs);

  double relative_norm_lu = (rhs - (H * sol_lu)).norm() / norm_en;

  std::cout << "\n\nTesting the solution: A*sol_lu=\n" /*final newline is necessary due to the formatting of the output of the vector*/ << H * sol_lu << "\n\n"
            << relative_norm_lu << "\nDoes it match?" << std::flush;
  //----------------UseLUEnd----------------

  return 0;
}
