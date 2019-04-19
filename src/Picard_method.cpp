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


/* Numerical algorithms | Picard Method
 * Regression formula: x_(n+1) = g(x_n)
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>

#define x0 0.1

int main()
{
    float xi, temp = 0;
    int counter = 0, presicion[] = {2,3,6,12};

    std::string title = "Picard method";
    std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
    std::cout << "x_0 = " << x0 << std::endl << std::endl;

    for (size_t i=0; i<4; ++i) {

        xi = x0;
        counter = 0;
        temp = 0;

        while (temp != xi) {
            temp = xi;
            xi = roundf( pow(10,presicion[i]) * (exp(2*xi)-1)/3 ) / pow(10,presicion[i]);	// presicion[i] signigicant decimal digits
            //std::cout << std::fixed << std::setprecision(presicion[i]) << "x_" << counter << " = " << xi << std::endl;
            ++counter;
        }

        std::cout << "Solution with " << std::setprecision(0) << presicion[i] << " significant decimal digits:"
        << std::fixed << std::setprecision(presicion[i]) << xi << "    " << "Iterations: " << counter << std::endl;
    }
}
