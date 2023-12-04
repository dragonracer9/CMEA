#include <Eigen/Sparse>
#include <iostream>
#include "writer.hpp"
#include <cmath>
#include <Eigen/SparseCholesky>
#include <stdexcept>

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;


//! Vector type
typedef Eigen::VectorXd Vector;


//! Our function pointer, typedef'd to make it easier to use
typedef double(*FunctionPointer)(double, double);

//----------------poissonBegin----------------
//! Create the Poisson matrix for 2D finite difference.
//! @param[out] A will be the Poisson matrix (as in the exercise)
//! @param[in] N number of elements in the x-direction
void createPoissonMatrix2D(SparseMatrix& A, int N) {
     // Fill the matrix A using setFromTriplets - method (see other exercise
    // for how to use it).
    A.resize(N*N, N*N);
// (write your solution here)
}
//----------------poissonEnd----------------


//----------------RHSBegin----------------
//! Create the Right hand side for the 2D finite difference
//! @param[out] rhs will at the end contain the right hand side
//! @param[in] f the right hand side function f
//! @param[in] N the number of points in the x direction
//! @param[in] dx the cell width
void createRHS(Vector& rhs, FunctionPointer f, int N, double dx) {
    rhs.resize(N * N);
    // fill up RHS
    // remember that the index (i,j) corresponds to i*N+j
// (write your solution here)
}
//----------------RHSEnd----------------


//----------------solveBegin----------------
//! Solve the Poisson equation in 2D
//! @param[out] u will contain the solution u
//! @param[in] f the function pointer to f
//! @param[in] N the number of points to use (in x direction)
void poissonSolve(Vector& u, FunctionPointer f, int N) {
    // Solve Poisson 2D here
// (write your solution here)
}
//----------------solveEnd----------------

//! Test if the Poisson matrix is correctly set up for one case
//! This does NOT guarantee that the code is correct, it is only a small
//! indication
void testPoissonMatrix() {
    SparseMatrix A;
    const int N = 13;
    createPoissonMatrix2D(A, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; j++) {

            if (i==j) {
                if ( A.coeff(i,j) != 4) {
                    throw std::runtime_error("Poisson matrix: Wrong Poisson matrix");
                }
            } else if (i == j - 1 || i == j + 1 || i == j+N || i == j-N) {
                if (A.coeff(i,j) != -1) {
                    throw std::runtime_error("Poisson matrix: Wrong upper or lower diagonals");
                }
            } else {
                if (A.coeff(i,j) != 0) {
                    throw std::runtime_error("Poisson matrix: Matrix is not band diagonal");
                }
            }
        }
    }
}

double F(double x, double y) {
    return 8*M_PI*M_PI*sin(2*M_PI*x)*sin(2*M_PI*y);
}



int main(int, char**) {
    Vector u;

    try {
        testPoissonMatrix();
    } catch (const std::exception& e) {
        std::cout << "Warning: " << e.what() << " (or not implemented)" << std::endl;
        return -1;
    }

    poissonSolve(u, F, 100);
    writeToFile("u_fd.txt", u);
}




