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
 
 This is a study of the stability of the Rugne-Kutta 2nd order method.
 Different step values are selected, in order to validate the theoritically
 expected range of step values that result at a stable sulution.
 
 Of course, the regression formulas are hard-coded for the given ODE, but one
 can just replace them with the formulas calculated for any ODE.
 
 ODE: y' = -10 * y^2 / x
 Initial value: y(0.1) = 1 
 Step values: h = [0.005, 0.01, 0.015, 0.02]
 Boundaries: [0.1, 1.1]
 
 More information can be found at 'Numerical_Methods_report.pdf'.
%}


% step values
h = [0.005, 0.01, 0.015, 0.02];

% boundaries
beginning = 0.1;
ending = 1.1;

% number of values (+1 for the initial-0th value)
n = ceil((ending - beginning) ./ h) + 1;

% rows: results for the different step values
% columns: y value of each step
y = zeros(size(n, 2), max(n));

% initialization
y(:,1) = 1;


% loop through h steps
for j = 1:4
  
  % vector of independent variable x
  x = [0.1:h(j):1.1];
  
  % If the step value doesn't divide the boundary exactly, the boundary would
  % not be included.
  if x(end) != 1.1
    x = [x 1.1];
  end

  % regression for Runge-Kutta 2nd order
  for i = 1:n(j)-1
    y(j, i+1) = y(j, i) - 5 * h(j) * (1 / x(i) + 1 / x(i+1)) * y(j, i)^2 ...
      + 100 * h(j)^2 / (x(i) * x(i+1)) * y(j, i)^3 ...
      + 500 * h(j)^3 / (x(i)^2 * x(i+1)) * y(j, i)^4;
  endfor
  
  % plotting to a grid 2x2
  subplot(2, length(h)/2, j)
  
  % Step values that result to instable solution give NANs.
  % Calculation of lenght of the vector of the results, discarding NANs
  plotLength = length(nonzeros(isfinite(nonzeros(y(j,:))'))');
  
  plot(x(1:plotLength), y(j, 1:plotLength));

endfor

% step stability check: |e_n+1 / e_n| < 1
stability = (0.005 - (0.2*h - 29*h.^2 + 2000*h.^3) ./ (0.1 + h)) >=0
