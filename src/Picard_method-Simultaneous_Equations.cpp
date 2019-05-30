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


/* 
 *Numerical algorithms | Picard Method with simultaneous equations
 * Regression formulas: x_(n+1) = f(x_n, y_n)
 *                      y_(n+1) = g(x_n, y_n)
 * 
 * Using the same equations as with the Newton method example, you can notice that the
 * solutions estimated with the Newton method are out of limits defined by convergence 
 * criteria of the Picard method. So, this program does not converge. For more details
 * read the Numerical_Methods_report.pdf .
 * 
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>

const double x_0 = 2.0;
const double y_0 = 1.4;

int main()
{
    double xi;
    double yi;
    double x_prev = 0;
    double y_prev = 0;
    int counter_x = 0;
    int counter_y = 0;
    int precision[] = {3,6,12};

    std::string title = "Picard method | Simultaneous equations";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << x_0 << "\ty_0 = " << y_0 << std::endl << std::endl;

    // Execute for various precision values
    for (size_t i = 0; i < 3; ++i) {

        xi = y_0;
        counter_x = 0;
        x_prev = 0;

        // Regression block for variable x
        while (x_prev != xi) {
            x_prev = xi;
            // precision[i] decimal places
            xi = round( pow(10, precision[i]) * (sqrt(3 - pow(xi, 2))) )
                / pow(10, precision[i]);
            ++counter_x;
            std::cout << std::fixed << std::setprecision(precision[i]) << "x_"
                << counter_x << " = " << xi << std::endl;
        }

        yi = x_0;
        counter_y = 0;
        y_prev = 0;		

        // Regression block for variable y
        while (counter_y < 10) {      //y_prev != yi
            y_prev = yi;
            // precision[i] decimal places
            yi = round( pow(10, precision[i]) * (sqrt((pow(yi, 2) - 2) / 3)) )
                / pow(10, precision[i]);
            ++counter_y;
            std::cout << std::setprecision(precision[i]) << "y_" << counter_y
                << " = " << yi << std::endl;
        }

        std::cout << "Solution with " << std::setprecision(0) << precision[i]
            << " decimal places: (x,y) = " << std::fixed << std::setprecision(precision[i])
            << "(" << xi << "," << yi << ")" << "\t" << "Iterations: x: " << counter_x
            << ", y: " << counter_y << std::endl << std::endl;

    }
}
