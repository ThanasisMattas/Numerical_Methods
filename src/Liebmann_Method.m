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
 Uxx(x,y) + Uyy(x,y) = f(x,y) -- Poisson's equation)

 A 2D grid of 400x400 = 160k nodes is used and, at the end of the program, a
 graph with the resulted values of the function u(x,y) is generated upon the grid.
 
 The solution progresses until tolerance reaches 10^-5 (line 69).
 
 
 Regression schemes:
                                           1
 Liebmann :         u_i,j(new) = 1/4 * [{1 0 1} u_i,j(old) - h^2 * f_i,j)]
                                           1

                                                         1
 Relaxed Liebmann : u_i,j(new) = u_i,j(old) + ω/4 * [{1 -4 1} u_i,j(old) - h^2 * f_i,j)]
                                                         1      
                    ω: relaxation factor
 
 
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
% initialization to zero
u = zeros(N, M);

% discretization step (N-1 devisions -> N grid points)
h = Lx / (N-1);

% tolerance value
TOL = 10^-5;

% max iterations
ITER_MAX = 100000;

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

% This holds the stepwise tolerance value
tolerance_vector = zeros(ITER_MAX, 1);

% regression block for Liebmann method
iter = 0;
while ++iter
  % u_new is (N-2) * (M-2)
  u_new = 1/4 * (u(3:M, 2:N-1) + u(2:M-1, 3:N) ...
    + u(1:M-2, 2:N-1) + u(2:M-1, 1:N-2) - h^2 * f_xy(2:M-1, 2:N-1));

  tolerance = 1 / ((N-2) * (M-2)) * sum(sum(abs(u_new - u(2:M-1, 2:N-1))));
  fprintf ('iter: %d   tolerance: %f\n', iter, tolerance);
  u(2:M-1, 2:N-1) = u_new;
  tolerance_vector(iter) = tolerance;
  
  if tolerance < TOL || iter > ITER_MAX
    break
  end
end

% this will be plotted
u_Liebmann = u;


% ------------------------------------------------------------------------------
% Successive Over Relaxation method (SOR).
program_title = 'SOR method';
fprintf('%s\n', program_title);
fprintf('%s\n',repmat('-', 1, length(program_title)));

% This holds the tolerance values of the SOR method.
tolerance_vector_sor = zeros(ITER_MAX, 1);

% At an orthonormal grid NxM, the ideal value of the overrelaxtion factor omega
% is the min root of:
% (cos(pi/(N-1)) + cos(pi/(M-1)))^2 * omega^2 - 16 * omega +16 = 0
alpha = (cos(pi/(N-1)) + cos(pi/(M-1)))^2;
discriminant = 256 - 4 * alpha * 16;
omega = ...
  min([(16 + sqrt(discriminant)) / (2*alpha),
  (16 - sqrt(discriminant)) / (2*alpha)]);

% In this example we will use underrelaxation, because overrelaxtion diverges.
% So, this is a relaxed/damped Leibmann method with relaxation factor omega:
omega =0.2;

% initialization of the grid to zero
u(2:M-1, 2:N-1) = zeros(M-2, N-2);

iter = 0;
while ++iter
  % u_new is (N-2) * (M-2)
  u_new = u(2:M-1, 2:N-1) + omega/4 * (u(3:M, 2:N-1) + u(2:M-1, 3:N) ...
    - 4 * u(2:M-1, 2:N-1) + u(1:M-2, 2:N-1) + u(2:M-1, 1:N-2) ...
    - h^2 * f_xy(2:M-1, 2:N-1));

  tolerance = 1 / ((N-2) * (M-2)) * sum(sum(abs(u_new - u(2:M-1, 2:N-1))));
  fprintf ('iter: %d   tolerance: %f\n', iter, tolerance);
  u(2:M-1, 2:N-1) = u_new;
  tolerance_vector_sor(iter) = tolerance;

  if tolerance < TOL || iter > ITER_MAX
    break
  end
end


% ------------------------------------------------------------------------------   
% plotting
clear('title');

% 1. tolerance convergence
figure(1);
plot(nonzeros(tolerance_vector));
set(gca, 'YScale', 'log')
title 'tolerance convergence'
xlabel iterations
ylabel tolerance
grid on
hold on;
plot(nonzeros(tolerance_vector_sor));
legend 'Liebmann method' 'Relaxed Liebmann method, ω = 0.2'

% 2. f(x,y)
figure(2);
[X,Y] = meshgrid(0:h:1, 0:h:1);

subplot(1, 2, 1);
surf(X, Y, f_xy)
title '\color{blue}f(x,y) = - 10 (x^2 + y ^2 + 5)'
xlabel x
ylabel y
zlabel 'f(x,y)'

% 3. solution
subplot(1, 2, 2);
surf(X, Y, u_Liebmann)
title (['Liebmann method on', ...
  ' \color{blue}\partial^2u(x,y)/\partialx^2', ...
  ' + \partial^2u(x,y)/\partialy^2', ...
  ' = - 10 * (x^2 + y ^2 + 5)'])
xlabel x
ylabel y
zlabel 'u(x,y)'
