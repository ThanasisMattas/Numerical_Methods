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
 Hyperbolic Partial Differential Equations | Lax-Wendroff method
 
 This program uses the Lax-Wendroff method, in order to numerically solve linear 
 hyperbolic PDEs with general form of:
 Utt(x,t) - a^2 * Uxx(x,t) = 0    -- wave function
 or
 Ut + a * Ux = 0
 
 Where a is the wave propagation speed.

 An 1D grid of 200 nodes is used and, at the end of the program, the numerical
 propagation of the pulse is plotted.
 
 
 Lax-Wendroff Regression scheme:

 u_(i)(new) = u_(i)(old) - c/2 * [u_(i+1)(old) - u_(i-1)(old)]
            + c^2/2 * [u_(i+1)(old) - 2 * u_(i)(old) + u_(i-1)(old)]
            
 Where c = a * t_step / h

 
 PDE: Utt(x,t) - a^2 * Uxx(x,t) = 0
 Wave propagation speed (a): sqrt(2) / pi;
 Grid length: x: 0-12
 Grid size: 1x200
 Discretization step (h): 12/199 = 0.06030
 Time step: 0.5 * h / a;
 
 Boundary conditions
 u(0,t) = 0
 u(12,t) = 0
 
 Initialization
 0 <= x < 2  : u(x,0) = 0
 2 <= x <= 4 : u(x,0) = sin(pi*x)
 4 < x <= 12 : u(x,0) = 0
 
 More information can be found at 'Numerical_Methods_report.pdf'.
%}

program_title = 'Lax-Wendroff';
fprintf('%s\n', program_title);
fprintf('%s\n',repmat('-', 1, length(program_title)));

% Number of grid nodes
N = 200;

% grid boundaries 
x0 = 0;
Lx = 12;

% 1D grid
u = zeros(1, N);

% wave propagation speed
a = sqrt(2) / pi;

% discretization step (N-1 devisions -> N grid points)
h = Lx / (N-1);

% x dimention values
x = [x0:h:Lx];
if x(end) != Lx
  x = [x Lx];
endif

% time step
t_step = 0.5 * h / a;

% boundary conditions
% u(0,t) = 0
% u(12,t) = 0
u(1) = 0;
u(end) = 0;

% initialization
% 0 <= x < 2  : u(x,0) = 0
% 2 <= x <= 4 : u(x,0) = sin(pi*x)
% 4 < x <= 12 : u(x,0) = 0
u(1: round(2/h) - 1) = 0;
u(round(2/h): round(4/h)) = sin(pi*[2:h:4]);
u(round(4/h) + 1: end) = 0;
u_init = u;

% total time steps for duration = 0, pi, ... , 5*pi
steps = ceil([0:pi:5*pi] ./ t_step);

% this holds the stepwise solution for the duration: 0 <= t <= 5*pi
u_stepwise = zeros(steps(end), N)

% this holds the tolerance value of each step
tolerance_vector = zeros(1, steps);

% Lax-Wendroff regression scheme:
% u_(i)(new) = u_(i)(old) - c/2 * [u_(i+1)(old) - u_(i-1)(old)]
%          + c^2/2 * [u_(i+1)(old) - 2 * u_(i)(old) + u_(i-1)(old)]
% c = a * t_step / h
c = a * t_step / h;

% loop through the different numbers of steps 
for i = 1:length(steps)
  
  u = u_init;
  
  % regression
  for iter = 1:steps(i)
    % u_new has N-2 points
    u_new = u(2:N-1) - c/2 * (u(3:N) - u(1:N-2)) ...
      + c^2/2 * (u(3:N) - 2 * u(2:N-1) + u(1:N-2));

    tolerance = 1 / (N-2)  * sum(abs(u_new - u(2:N-1)));
    fprintf ('iter: %d   tolerance: %f\n', iter, tolerance);
    u(2:N-1) = u_new;
    tolerance_vector(iter) = tolerance;
    
    u_stepwise(iter, :) = u;
  endfor
  
  % plotting
  clear('title');

  % 1. tolerance convergence
  figure(1);
  plot(nonzeros(tolerance_vector));
  % set(gca, 'YScale', 'log')
  title 'tolerance convergence'
  xlabel iterations
  ylabel tolerance
  legend 'π' '2π' '3π' '4π' '5π'
  grid on
  hold on

  % 2. solution
  figure(2);
  subplot(1, 2, 1);
  plot(x, u);
  title 'Lax-Wendroff on Utt - a^2Uxx = 0'
  xlabel x
  ylabel u(x,t)
  legend '0' 'π' '2π' '3π' '4π' '5π'
  grid on
  hold on
  
endfor

% 3. x-t-u(x,t)
figure(2);
subplot(1, 2, 2);
[X,Y] = meshgrid(x, 0:t_step:5*pi);
surf(X, Y, u_stepwise)
title 'Lax-Wendroff on Utt - a^2Uxx = 0'
xlabel x
ylabel t
zlabel 'u(x,t)'
ylim([0 5*pi])
yticks([0:pi:5*pi])
yticklabels({'0','\pi','2\pi','3\pi','4\pi','5\pi'})
