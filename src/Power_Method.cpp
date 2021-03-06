/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


/* Numerical algorithms | Power Method
 *
 * This program uses the Power Method to find the greatest eigenvalue of
 * any square matrix (only by editing "const int N" and mySqVect [line 104]
 * -- current example: 6x6).
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <memory>

//! N: dimension of the square matrix
const int N = 6;

typedef std::vector<size_t> vector_int;
typedef std::vector< std::vector<size_t> > vector_int_2D;

//! A function that returns a given power of a given square matrix
vector_int_2D sqVectPow(vector_int_2D& inputSqVect, int power)
{
    vector_int_2D newSqVect(inputSqVect);       // this will be eventually returned
    vector_int_2D tempSqVect(N, vector_int(N)); // this will hold the step-wise solution

    // unroll power to multiplications
    for (size_t k = 1; k < power; ++k) {

        // initialize tempSqVect to zeros
        for (auto& i : tempSqVect)
            std::fill(i.begin(), i.end(), 0);

        // temp = new * input
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {  
                for (size_t l = 0; l < N; ++l) {
                tempSqVect[i][j] += newSqVect[i][l] * inputSqVect[l][j];
                }
            }
        }

        // newSqVect = tempSqVect
        // and tempSqVect = newSqVect, but tempSqVect will be set to zero
        newSqVect.swap(tempSqVect);
    }
    return newSqVect;
}

//! A function that returns the vector x^(n) = A^n * x , where A is the square matrix,
//! n is the power of the square matrix and x is the arbitrary vector.
std::unique_ptr<vector_int> x_n(vector_int_2D&& poweredSqVect_input,
                                vector_int& arbitrary_vector)
{
    std::unique_ptr<vector_int> x_n = std::make_unique<vector_int>(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            (*x_n)[i] += poweredSqVect_input[i][j] * arbitrary_vector[j];
        }
    }
    return x_n;
}

//! A function that returns the greatest element of vector x^(n) = A^n * x , where A is
//! the square matrix,n is the power of the square matrix and x is the arbitrary vector.
double GreatestElement(std::unique_ptr<vector_int> x_n)
{
    return *std::max_element((*x_n).begin(), (*x_n).end());
}

int main()
{
    std::string title = "Power Method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;

    //! A random 6x6 matrix. You can work with square matrices of other dimension,
    //! only by editing 'const int N' [line 31]
    vector_int_2D mySqVect {{6, 0, 2, 3, 2, 4},
                            {4, 1, 8, 0, 3, 5},
                            {7, 3, 3, 2, 9, 0},
                            {4, 0, 0, 2, 6, 1},
                            {1, 6, 3, 4, 5, 6},
                            {2, 8, 4, 3, 9, 0}};

    //! arbitrary selection of N-element vector x = (1, 1, 1, 1, 1, 1)^T (convenience)
    vector_int x(N,1);

    int iter;

    //! greatest eigenvalue
    double l;
    double l_prev;

    int precision[] = {2, 3, 5};

    /* Main regression block
     *
     * Repeat the evaluation of the greatest eigenvalue, using different precision
     * values.
     */
    for (size_t pr = 0; pr < 3; ++pr) {

        iter = 0;
        l_prev = 0;

        while (l != l_prev) {

            ++iter;
            l_prev = l;

            l = GreatestElement(x_n(sqVectPow(mySqVect, iter+1), x))
                / GreatestElement(x_n(sqVectPow(mySqVect, iter), x));
            l = round(pow(10, precision[pr]) * l) / pow(10, precision[pr]);

            std::cout << std::fixed << std::setprecision(0) << "Iter #" << iter
                << "   " << std::setprecision(precision[pr]) << "l = " << l
                << std::endl;
        }

        std::cout << "----------------------\nGreatest Eigenvalue with "
            << std::setprecision(0) << precision[pr] << " decimal digits: "
            << std::setprecision(precision[pr]) << l << "  |  " << "Iterations: "
            << iter << std::endl << "Corresponding Eigenvector (normalized): (";

        for (size_t i = 0; i< (*x_n(sqVectPow(mySqVect, iter+1), x)).size(); ++i) {
            std::cout << (*x_n(sqVectPow(mySqVect, iter+1), x))[i]
                / GreatestElement(x_n(sqVectPow(mySqVect, iter+1), x)) << ", ";
        }
        std::cout << "\b\b)" << "\n\n\n";
    }
}
