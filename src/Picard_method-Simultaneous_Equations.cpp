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
 * solutions estimated with the Newton method are out of limits defined by  convergence 
 * criteria of the Picard method. So, this program does not converge. For more details
 * read the Numerical_Methods_report.pdf .
 * 
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>

#define x0 2
#define y0 1.4

int main()
{
    float xi, yi, temp = 0;
    int counter_x = 0, counter_y = 0, presicion[] = {3,6,12};

    std::string title = "Picard method | Simultaneous equations";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << x0 << "\ty_0 = " << y0 << std::endl << std::endl;

    for (size_t i=0; i<3; ++i) {

        xi = y0;
        counter_x = 0;
        temp = 0;

        while (temp != xi) {
            temp = xi;
            // presicion[i] signigicant decimal digits
            xi = roundf( pow(10,presicion[i]) * ( sqrt(3-pow(xi,2)) ) / pow(10,presicion[i]));
            ++counter_x;
            std::cout << std::fixed << std::setprecision(presicion[i]) << "x_" << counter_x << " = " << xi << std::endl;
        }

        yi = x0;
        counter_y = 0;
        temp = 0;		

        while (temp != yi) {
            temp = yi;
            // presicion[i] signigicant decimal digits
            yi = roundf( pow(10,presicion[i]) * ( sqrt((pow(yi,2) -2)/3)) / pow(10,presicion[i]));
            ++counter_y;
            std::cout << std::setprecision(presicion[i]) << "y_" << counter_y << " = " << yi << std::endl;
        }

        std::cout << "Solution with " << std::setprecision(0) << presicion[i] <<" significant decimal digits: (x,y) = "
        << std::fixed << std::setprecision(presicion[i]) << "(" << xi << "," << yi << ")" << "\t" << "Iterations: x: "
        << counter_x << ", y: " << counter_y << std::endl;

    }
}

