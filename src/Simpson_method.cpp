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


/* Numerical algorithms | Numerical Integration | Simpson method
 *
 * This program uses the Simpson Method to evaluate a given definite integral
 * I (limits: [a, b]). The intention is to compare the interval partitions
 * needed, as opposed with the evaluation by the Filon method, using 5 points.
 * 
 * Simpson method:
 * I = h/2 (f_0 + 4f_1 + 2f_2 + ... + 2f_(n-2) + 4f_(n-1) + f_n)
 * 
 * where h is the discretization step
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>

// The integration range (b - a = 4π)
const double range = 4 * M_PI;

// Decimal places
const int precision = 5;

// The fucntion to be integrated
double f(double x)
{
    return exp(x - 10.0) * sin(10.0 * x);
}

// f(a) and f(b)
const double f_a = f(0);
const double f_b= f(range);

// Discretization step
double h(int points)
{
    return range / (points -1);
}

/* Simpson method
 * returns the integral evaluated for given divisions of the integration range
 */
double simpsonMethod(int points)
{
    // Initialize sum with f(a) + f(b)
    double sum = f_a + f_b;

    for (size_t i = 1; i <= points - 2; ++i) {
        if (i % 2) {
            sum += 4 * f(i * h(points));
        }
        else {
            sum += 2 * f(i * h(points));
        }
    }

    // Evaluation of the integral, rounding at a given precision
    double I = round((h(points) / 3 * sum) * pow(10, precision)) / pow(10, precision);

    return I;
}

// Evaluates the residual at each iteration
double residual(double prev, double current)
{
    return fabs(prev - current);
}

int main()
{
    std::string title = "Numerical Integration using the Simpson method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;

    double I = 0;
    double I_prev = 0;
    int points = 3;
    int iter = 0;

    /* Evaluation of the points needed by the Simpson method, in order to estimate the
     * integral with the same precision estimated using the Filon method with 5 points.
     * 
     * In order to just compute the integral, a user can define a residual threshold
     * as a terminating condition, at the bellow while statement.
     * eg: (residual(I_prev, I) > 0.001 || I == 0)
     * --to prevent evaluating I == 0 at every iteration, an initialization is needed-- 
     */
    std::cout << "Iter   points  Integral    Residual   Time(s)" << std::endl;

    while (round(1000 * I) / 1000 != -1.302) {

        ++iter;
        I_prev = I;
        I = simpsonMethod(points);

        // Every 15 lines, print the titles.
        if (iter % 15 == 0) {
            std::cout << "Iter   points  Integral    Residual   Time(s)" << std::endl;
        }

        // Print the data of the iteration
        std::cout
            << iter
            << std::string(7 - std::to_string(iter).length(), ' ')
            << points
            << std::string(8 - std::to_string(points).length(), ' ')
            << std::fixed << std::setprecision(precision)
            << I
            << std::string(13 - std::to_string(I).length(), ' ')
            << residual(I_prev, I)
            << std::string(12 - std::to_string(residual(I_prev, I)).length(), ' ')
            << clock() / (double)CLOCKS_PER_SEC
            << std::endl;
		
        // points must always be odd, in order to partition the interval into even
        // number of divisions, which is required by the Simpson method.
        points += 2;
    }
}
