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


/* Numerical algorithms | Gauss-Seidel Method
 *
 * This program solves any 3x3 linear system of equations (you just need to
 * edit the formulas at the regression block and the initial values), using
 * the Gauss-Seidel Method.
 * 
 * Current example:
 * 
 *                   20x +   y -  2z =  17
 *                    3x + 20y +   z = -18
 *                    2x -  3y + 20z =  25 
 * 
 *                             or
 * 
 *                 20   1  -2     x      17
 *                  3  20   1  *  y  =  -18
 *                  2  -3  20     z      25
 */


#include <iostream>
#include <cmath>
#include <iomanip>

const double x_0 = 2.0;
const double y_0 = 0.0;
const double z_0 = 2.0;

int main()
{
	
    double xi, yi, zi;
    double x_prev = 0, y_prev = 0, z_prev = 0;
    unsigned counter = 0, precision[] = {3, 9, 12};
        
    std::string title = "Gauss-Seidel method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << x_0 << ",\ty_0 = " << y_0 << ",\tz_0 = " << z_0
        << std::endl << std::endl;
        
    // loop through precision values, in order to compare the iterations required
    for (size_t i = 0; i < 3; ++i) {
            
        xi = x_0, yi = y_0, zi = z_0;
        counter = 0;
                
        // convergance occurs when all parameters converge
        while ( xi != x_prev || yi != y_prev || zi != z_prev ) {

            x_prev = xi;
            y_prev = yi;
            z_prev = zi;

            // precision[i] decimal places
            xi = round( pow(10, precision[i]) * ((17 - yi + 2*zi)/20) ) / pow(10, precision[i]);
            yi = round( pow(10, precision[i]) * ((-17 - 3*xi - zi)/20) ) / pow(10, precision[i]);
            zi = round( pow(10, precision[i]) * ((25 - 2*xi + 3*yi)/20) ) / pow(10, precision[i]);
                    
            ++counter;

            std::cout << "Iter #" << counter << ": " << std::fixed << std::setprecision(precision[i])
                << "x_" << counter << " = " << xi << "  "
                << "y_" << counter << " = " << yi << "  "
                << "z_" << counter << " = " << zi << std::endl;
        }

        std::cout << "-------------------\nSolution with " << std::setprecision(0) << precision[i]
            << " decimal places: (x,y,z) = " << std::setprecision(precision[i]) << "(" << xi
            << "," << yi << "," << zi << ")" << "  |  " << "Iterations: " << counter << std::endl
            << std::endl;
    }
}
