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
 Numerical algorithms | Boundary conditions problems | Runge-Kutta method
 
 This program solves a boundary conditions problem, using the shooting method
 and solving with the Runge-Kutta 2nd order method.
 
 Notice that the regression formulas are hard-coded for the given ODE, but one
 can just replace them with the formulas calculated for any ODE.
 
 ODE: y'' = -2y' + 8y
 Boundary values (Dirichlet type): y(0) = 1, y(1) = 0
 Step h = 0.01
 Boundaries: [0, 1]
 
 More information can be found at 'Numerical_Methods_report.pdf'.
%}


% step
h = 0.01;

% boundaries
a = 0;
b = 1;

% number of values (+1 for the initial-0th value)
n = ceil((a - b) / h) + 1;

% y and derivative dy/dx of each step
y = zeros(1, n);
y_der = zeros(1, n);

% initialization: y(a) = y(0) = 1
y(1) = 1;

% y(b) = y(1) = 0;
y_b = 0;

% The first derivative values selected for the shooting method and the resulted
% one, after implementing linear interpolation
% y1'(0) = -3, y2'(0) = -5 and after linear interpolation: y3'(0) = -4.0418
y_der_init = [-3, -5, -4.0418];

% this will hold the results of the shooting method
y_b_shooting = zeros(1, 3);

% loop through the inital values of y'(0)
for j = 1:3
  
  % initialization
  y_der(1) = y_der_init(j);

  % regression for Runge-Kutta 2nd order
  for i = 1:n-1
    y(i+1) = 1.0004 * y(i) + 0.0099 * y_der(i);
    y_der(i+1) = 0.0792 * y(i) + 0.9802 * y_der(i);
  endfor

  % store the result
  y_b_shooting(j) = y(end);
     
endfor

% Printing the results
fprintf('Real value of y(b) = %d\n', y_b)
fprintf('y1_der(a) = %.2f -> y1(b) = %f\n',...
  y_der_init(1), y_b_shooting(1))
fprintf('y2_der(a) = %.2f -> y2(b) = %f\n',...
  y_der_init(2), y_b_shooting(2))
fprintf('After linear interpolation: y3_der(a) = %f\nTesting it back to RK2 -> y3(b) = %f\n',...
  y_der_init(3), y_b_shooting(3))
