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


/* Numerical algorithms | Newton-Raphson Method
 * Regression formula: x_(n+1) = x_n - f(x_n)/f'(x_n)
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>

const float x0 = 0.1;
const float x00 = 0.203;

int main()
{
    float xi, x_prev = 0;
    int counter = 0, precision[] = {2,3,6,12};

    std::string title = "Newton-Raphson method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << x0 << std::endl << std::endl;

    // Execute for various precision values
    for (size_t i=0; i<4; ++i) {

        xi = x0;
        counter = 0;
        x_prev = 0;

        while (x_prev != xi) {
            x_prev = xi;

            // In order not to print zero
            if( !roundf( pow(10, precision[i]) * (xi - (exp(2*xi)-3*xi-1)/(2*exp(2*xi)-3)) )
                / pow(10, precision[i]) )
                break;

            // precision[i] decimal places
            xi = roundf( pow(10, precision[i]) * (xi - (exp(2*xi)-3*xi-1)/(2*exp(2*xi)-3)) )
                / pow(10, precision[i]);
            ++counter;
            std::cout << std::setprecision(precision[i])
                << "x_" << counter << " = " << xi << std::endl;
        }

        std::cout << "Solution with " << std::setprecision(0) << precision[i]
            << " significant decimal digits:" << std::fixed << std::setprecision(precision[i])
            << xi << "\t"<<"Iterations: " << counter << std::endl << std::endl;
    } 	


    /* 2.b
     *
     * Selecting a starting point that lies after the extremum (min) of the equation,
     * x00 = 0.203, leads to the other root of the equation, x = 0.3813
     */
    std::cout << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << std::setprecision(3) << x00 << std::endl << std::endl;

    // Execute for various precision values
    for (size_t i=0; i<3; ++i) {

        xi = x00;
        counter = 0;
        x_prev = 0;

        while (x_prev != xi) {
            x_prev = xi;

            if( !roundf( pow(10,precision[i]) * (xi - (exp(2*xi)-3*xi-1)/(2*exp(2*xi)-3)) )
                / pow(10,precision[i]) )
                break;
            
            // precision[i] decimal places
            xi = roundf( pow(10,precision[i]) * (xi - (exp(2*xi)-3*xi-1)/(2*exp(2*xi)-3)) )
                / pow(10,precision[i]);
            ++counter;
            // std::cout << std::setprecision(precision[i])
            //     << "x_" << counter << " = " << xi << std::endl;
        }

        std::cout << "Solution with " << std::setprecision(0) << precision[i]
            << " decimal places:" << std::fixed << std::setprecision(precision[i])
            << xi << "    " << "Iterations: " << counter << std::endl << std::endl;
    } 	
}
