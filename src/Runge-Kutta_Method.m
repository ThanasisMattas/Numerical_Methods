%{
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
%}


%{
 Numerical algorithms | Differential equations | Runge-Kutta method
 
 This program uses the 2nd and 4th order of Runge-Kutta method, in order
 to solve numerically the 2nd order differential equation of the harmonic
 oscillator [y'' + ω^2 y = 0 , ω: angular frequency].

 Of course, there is an analytical solution, but the validity of the numerical
 approach can be easily verified.
 
 The solutions of the two methods are displayed at the same plot, exhibiting
 that the graphs are diverging, while iterations advance, due to the step-wise
 propagation of different errors (different errors are summing up).
 
 Order of error:
 - 2nd order RK (same as Euler-Heum): O(h^3)
 - 4th order RK                     : O(h^4)
 
 
 Differential equation: y'' + 4^2 y = 0
 ω = 4
 Initial values: y(0) = 1, y'(0) = 0 
 Step: h = 0.1
 Boundaries: [0, 6]
 
 More information can be found at 'Numerical_Methods_report.pdf'.
%}


% step
h = 0.1;

% boundaries
beginning = 0;
ending = 6;

% number of values/steps (+1 for the initial-0th value)
n = (ending - beginning) / h + 1;

% y2 for Runge-Kutta 2nd order, y4 for 4th order
y2 = zeros(1, n);
y4 = zeros(1, n);

% derivative dy/dx of each step
y2_der = zeros(1, n);
y4_der = zeros(1, n);

% initialization
y2(1) = 1;
y4(1) = 1;
y2_der(1) = 0;
y4_der(1) = 0;


for i = 1:n-1
  
  % regression for Runge-Kutta 2nd order
  y2(i+1) = 0.9615385 * (0.96 * y2(i) + 0.1 * y2_der(i));
  y2_der(i+1) = y2_der(i) - 0.8 * y2(i) - 0.8 * y2(i+1);
  
  % regression for Runge-Kutta 4nd order
  y4(i+1) = 0.9210667 * y4(i) + 0.0985333 * y4_der(i);
  y4_der(i+1) = -1.5573333 * y4(i) + 0.9201067 * y4_der(i);

endfor


% plotting
x = [0:0.1:6];

plot(x, y2, 'b')
hold on
plot(x, y4, 'r')

xlabel x
ylabel y
legend 'Runge-Kutta 2nd order' 'Runge-Kutta 4nd order'
title 'Runge-Kutta on harmonic oscillator'
set(gcf,'Color', [0.75, 0.75, 0.75])
