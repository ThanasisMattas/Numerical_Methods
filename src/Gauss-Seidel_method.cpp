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

#define x0 2
#define y0 0
#define z0 2

int main()
{
	
    double xi, yi, zi;
    double x_prev = 0, y_prev = 0, z_prev = 0;
    unsigned counter = 0, presicion[] = {3,9,12};
        
    std::string title = "Gauss-Seidel method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x0 = " << x0 << ",\ty0 = " << y0 << ",\tz0 = " << z0 << std::endl << std::endl;
        
    // loop through presicion values | In order to compare the iterations required
    for (size_t i=0; i<3; ++i) {
            
        xi = x0, yi = y0, zi = z0;
        counter = 0;
                
        // convergance occurs when all parameters converge
        while ( xi != x_prev || yi != y_prev || zi != z_prev ) {

            x_prev = xi;
            y_prev = yi;
            z_prev = zi;

            // presicion[i] signigicant decimal digits
            xi = round( pow(10,presicion[i]) * ( (17 - yi + 2*zi)/20 )) / pow(10,presicion[i]);
            yi = round( pow(10,presicion[i]) * ( (-17 - 3*xi - zi)/20 )) / pow(10,presicion[i]);
            zi = round( pow(10,presicion[i]) * ( (25 - 2*xi + 3*yi)/20 )) / pow(10,presicion[i]);
                    
            ++counter;

            std::cout << "Iter #" << counter << ": "
            << "x" << counter << " = " << std::fixed << std::setprecision(presicion[i]) << xi << "  "
            << "y" << counter << " = " << yi << "  "
            << "z" << counter << " = " << zi << std::endl;
        }

        std::cout << "-------------------\nSolution with " << std::setprecision(0) << presicion[i]
        << " significant decimal digits: (x,y,z) = " << std::setprecision(presicion[i]) << "(" << xi
        << "," << yi << "," << zi << ")" << "  |  " << "Iterations: " << counter << std::endl << std::endl;
    }
}