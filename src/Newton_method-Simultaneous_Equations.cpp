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


/* Numerical algorithms | Newton Method with simultaneous equations
 * Regression formulas: x_(n+1) = x_n - (f*g_y - g*f_y) / (f_x*g_y - g_x*f_y)
 *                      y_(n+1) = y_n - (g*f_x - f*g_x) / (f_x*g_y - g_x*f_y)
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>

#define x0 1.5
#define y0 0.8

int main(){
	
	double xi, yi, temp = 0;
	int counter_x = 0, counter_y = 0, presicion[] = {3,6,12};
	
	std::string title = "Newton method | Simultaneous Equations";
	std::cout << title << std::endl << std::string(title.length(), '-') << std::endl;
	std::cout << "x_0 = " << x0 << "\ty_0 = " << y0 << std::endl << std::endl;
	
		
	for(size_t i=0; i<3; ++i){
		
		xi = x0;
		counter_x = 0;
		temp = 0;
		
		while(temp != xi){
			temp = xi;
			if( xi == round( pow(10,presicion[i]) * ( xi - (4*pow(xi,2)-11)/(8*xi) )) / pow(10,presicion[i]) )
			break;
			xi = round( pow(10,presicion[i]) * ( xi - (4*pow(xi,2)-11)/(8*xi) )) / pow(10,presicion[i]);	// presicion[i] signigicant floating digits
			++counter_x;
			std::cout << "x_" << counter_x << " = " << std::fixed << std::setprecision(presicion[i]) << xi << std::endl;
		}
		
		yi = y0;
		counter_y = 0;
		temp = 0;		
		
		while(temp != yi){
			temp = yi;
			if( yi == round( pow(10,presicion[i]) * ( yi - (4*pow(yi,2)-1)/(8*yi) )) / pow(10,presicion[i]) )
			break;
			yi = round( pow(10,presicion[i]) * ( yi - (4*pow(yi,2)-1)/(8*yi) )) / pow(10,presicion[i]);	// presicion[i] signigicant floating digits
			++counter_y;
			std::cout << std::setprecision(presicion[i]) << "y_" << counter_y << " = " << yi << std::endl;
		}		
		
		std::cout << "Solution with " << std::setprecision(0) << presicion[i] <<" significant floating digits: (x,y) = "
		<< std::setprecision(presicion[i]) << "(" << xi << "," << yi << ")" << "\t" << "Iterations: x: " << counter_x
		<< ", y: " << counter_y << std::endl << std::endl;
	}
}
