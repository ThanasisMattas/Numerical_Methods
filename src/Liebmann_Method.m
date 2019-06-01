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
 Numerical algorithms | 
 Elliptic Partial Differential Equations | Liebmann method
 
 This program uses the Liebmann method, in order to numerically solve elliptic
 PDEs (2nd order partial differential equations with general form of:
 Uxx(x,y) + Uyy(x,y) = f(x,y) )

 A 2D grid of 400x400 = 160k nodes is used and, at the end of the program, a
 graph with the resulted values of the function u(x,y) is generated upon the grid.
 
 The solution progresses until tolerance reaches 10^-5 (line 89).
 
 
 PDE: Uxx(x,y) + Uyy(x,y) = -10 (x^2 + y^2 + 5)
 Grid length: x: 0-1, y: 0-1
 Grid size: 400x400
 Discretization step: 1/400 = 0.0025
 Boundary conditions:
 u(0,y) = 0
 u(1,y) = 0
 u(x,0) = 0
 u(x,1) = 1
 
 More information can be found at 'Numerical_Methods_report.pdf'.
%}

program_title = 'Liebmann method';
fprintf('%s\n', program_title);
fprintf('%s\n',repmat('-', 1, length(program_title)));

% Number of x coordinate points
N = 400;

% Number of y coordinate points
M = 400;

% grid boundaries 
Lx = 1;
Ly = 1;

% orthonormal grid nodes: NxM = 400x400
u = zeros(N, M);

% discretization step 
h = Lx / N;

% boundary conditions
% u(0,y) = 0
% u(1,y) = 0
% u(x,0) = 0
% u(x,1) = 1
u(:, 1) = 0;
u(:, N) = 0;
u(1, :) = 0;
u(M, :) = 1;

% f(x,y) = -10 * (x^2 + y^2 +5)
% In order to calculate the (N-2)x(M-2) matrix f(x,y), the matrices of the
% x, y coordinates are needed.
%
% problem index: 0 - 399
% matlab/octave index: 1 - 400
x = h * [0:N-1] .* ones(N)(:, N);
y = h * [0:M-1]' .* ones(M)(M, :);

f_xy = -10 * (x.^2 + y.^2 + 5);


% regression block for Liebmann method
iter = 0;
while ++iter
  % u_new is (N-2) * (M-2)
  u_new = 1/4 * (u(3:M, 2:N-1) + u(2:M-1, 3:N) ...
    + u(1:M-2, 2:N-1) + u(2:M-1, 1:N-2) - h^2 * f_xy(2:M-1, 2:N-1));

  tolerance = 1 / ((N-2) * (M-2)) * sum(sum(abs(u_new - u(2:M-1, 2:N-1))));
  fprintf ('iter: %d   tolerance: %f\n', iter, tolerance);
  u(2:M-1, 2:N-1) = u_new;
  
  if tolerance < 10^-5 || iter > 50000
    break
  end
end
 
    
% plotting
clear('title');
[X,Y] = meshgrid(0:h:1-h, 0:h:1-h);

subplot(1, 2, 1);
surf(X, Y, f_xy)
title '\color{blue}f(x,y) = - 10 (x^2 + y ^2 + 5)'
xlabel x
ylabel y
zlabel 'f(x,y)'

subplot(1, 2, 2);
surf(X, Y, u)
title (['Liebmann method on', ...
  ' \color{blue}\partial^2u(x,y)/\partialx^2', ...
  ' + \partial^2u(x,y)/\partialy^2', ...
  ' = - 10 * (x^2 + y ^2 + 5)'])
xlabel x
ylabel y
zlabel 'u(x,y)'
