%--------------------------------------------------------------------------
%
%    solve1DConvectionDiffusionEquation.m
%
%    - A script to set up and solve the 1D convection- diffusion equation
%    for heat conduction in a fluid moving at constant velocity
%
%    [Chapter 3]
%
%    Author: HuuKhai-Nguyen
%
%    - Email: khaikn249@gmail.com
%    - LinkedIn: https://www.linkedin.com/in/khai-nguyen-741b2519a/
%    - Lab website: https://simtec.vn/
%
%   
%
%--------------------------------------------------------------------------
close all; clear; clc
%--------------------------------------------------------------------------
% User Inputs
%--------------------------------------------------------------------------

% Thermal Conductivity of the fluid (W/mK)
cond = 100;

% Specific heat capacity of the bar (J/Kg K)
cp = 1000;

% Cross-sectional Area of the channel (m2)
area = 0.1;

% Length of the channel (m)
barLength = 5;

% Number of cells in the mesh
nCells = 5;

% Temperature at the left hand side of the channel (deg C)
tempLeft = 100;

% Temperature at the right hand side of the channel (deg C)
tempRight = 200;

% Heat source per unit volume (W/m3)
heatSourcePerVol = 1000;

% Flow velocity (m/s)
flowVelocity = 0.01;

% Fluid Density (kg/m3)
fluidDensity = 1.0;

% Plot the data? ('true' / 'false')
plotOutput = 'true';

% Print the set up data? (table of coefficients and matrices)
printSetup = 'true';

% Print the solution output (the temperature vector)
printSolution = 'true';

% =========================================================================
% Code Begins Here
% =========================================================================
%--------------------------------------------------------------------------
% 1. Print messages
%--------------------------------------------------------------------------

fprintf('================================================\n');
fprintf('\n');
fprintf('   solve1DConvectionDiffusionEquation.m\n')
fprintf('\n')
fprintf('================================================\n')

%--------------------------------------------------------------------------
% 2. Create the mesh of cells
%--------------------------------------------------------------------------

fprintf(' Creating Mesh ...\n');
fprintf('------------------------------------------------\n');

% Start by calculating the coordinates of the cell faces
xFaces = linspace(0, barLength, nCells+1);

% Calculate the coordinates of the cell centroids
xCentroids = 0.5*(xFaces(2:end) + xFaces(1:end-1));

% Calculate the length of each cell
cellLength = xFaces(2:end) - xFaces(1:end-1);

% Calculate the distance between cell centroids
dCentroids = xCentroids(2:end) - xCentroids(1:end-1);

% For the boundary cell on the left, the distance is double the distance
% from the cell centroid to the boundary face
dLeft = 2*(xCentroids(1) - xFaces(1));

% For the boundary cell on the right, the distance is double the distance from
% the cell centroid to the boundary cell face
dRight = 2*(xFaces(end) - xCentroids(end));

% Append these to the vector of distances
dCentroids = [dLeft, dCentroids, dRight];

% Compute the cell volume
cellVolumes = cellLength*area;

%--------------------------------------------------------------------------
% 2.0 Calculate the Matrix Coefficients
%--------------------------------------------------------------------------

fprintf(' Calculating Matrix Coefficients\n');
fprintf('------------------------------------------------\n');

% Diffusive flux per unit area
DA = area*cond./dCentroids;

% Convective flux
velocityVector = flowVelocity*ones(1, nCells+1);
densityVector = fluidDensity*ones(1, nCells+1);
F = densityVector.*velocityVector*area*cp;

% Evaluate the Peclet Number
Pe = F./DA;

% Calculate the source term Sp
Sp = zeros(1, nCells);

% Assign sources to the left and right hand boundaries
Sp(1) = -1.0*(2.0*DA(1) + F(1));
Sp(end) = -1.0*(2.0*DA(end) - F(end));

% Calculate the source term Su
Su = heatSourcePerVol*cellVolumes;

% Assign sources to the left and right hand boundaries
Su(1) = Su(1) + (2.0*DA(1) + F(1))*tempLeft;
Su(end) = Su(end) + (2.0*DA(end) - F(1))*tempRight;

% Left Coefficient (aL)
aL = DA(1:end-1) + 0.5*F(1:end-1);

%Right Coefficient (aR)
aR = DA(2:end) - 0.5*F(2:end);

% Set the first element of aL to zero. It is a boundary face
aL(1) = 0;

% Set the last element of aR to zero. It is a boundary face
aR(end) = 0;

% Create the central coefficients
aP = aL + aR - Sp;

%--------------------------------------------------------------------------
% 3.0 Create the matrices
%--------------------------------------------------------------------------

fprintf(' Assembling Matrices\n');
fprintf('------------------------------------------------\n');

% Start by creating an empty A matrix and an empty B matrix
Amatrix = zeros(nCells, nCells);
BVector = zeros(nCells, 1);

% Populate the matrix one row at a time (i.e one cell at a time)
%
% NOTE: this method is deliberately inefficient for this problem
% but it is useful for learning purposes. We could populate the
% diagonals and the off-diagonals directly.

for i = 1:nCells

    % Do the A matrix Coefficients

    % Left boundary Cell
    if (i == 1)

        Amatrix(i, i) = aP(i);
        Amatrix(i, i+1) = -1.0*aR(i);

    % Right Boundary Cell
    elseif(i == nCells)

        Amatrix(i, i-1) = -1.0*aL(i);
        Amatrix(i, i) = aP(i);

    % Interior Cells
    else

        Amatrix(i, i-1) = -1.0*aL(i);
        Amatrix(i, i) = aP(i);
        Amatrix(i, i+1) = -1.0*aR(i);
    end
    
    % Do the B matrix coefficients
    BVector(i) = Su(i);
end

%--------------------------------------------------------------------------
% 4.0 Print the setup
%--------------------------------------------------------------------------

if strcmp(printSetup, 'true')
    fprintf(' Summary: Set Up\n')
    fprintf('------------------------------------------------\n')
    fprintf('aL: ')
    for i = 1:nCells
       fprintf('%6.1f ', aL(i)); 
    end
    fprintf('\n')
    fprintf('aR: ')
    for i = 1:nCells
       fprintf('%6.1f ', aR(i)); 
    end
    fprintf('\n')
    fprintf('aP: ')
    for i = 1:nCells
       fprintf('%6.1f ', aP(i)); 
    end
    fprintf('\n')
    fprintf('Sp: ')
    for i = 1:nCells
       fprintf('%6.1f ', Sp(i)); 
    end
    fprintf('\n')
    fprintf('Su: ')
    for i = 1:nCells
       fprintf('%6.1f ', Su(i)); 
    end
    fprintf('\n')
    fprintf('Pe: ')
    for i = 1:nCells+1
       fprintf('%6.1f ', Pe(i)); 
    end
    fprintf('\n')
    fprintf('A matrix:\n')
    for i = 1:nCells
        for j = 1:nCells
           fprintf('%6.1f ', Amatrix(i, j)); 
        end
        fprintf('\n')
    end
    fprintf('B vector:\n')
    for i = 1:nCells
       fprintf('%6.1f\n', BVector(i)); 
    end
    fprintf('\n')
    fprintf('------------------------------------------------\n')
end

%--------------------------------------------------------------------------
% 5.0 Solve the matrices
%--------------------------------------------------------------------------

fprintf(' Solving ...\n')
fprintf('------------------------------------------------\n')

% Use MATLAB's default linear algebra solver (AX = B)
Tvector = Amatrix \ BVector;

fprintf(' Equations Solved.\n')
fprintf('------------------------------------------------\n')

%--------------------------------------------------------------------------
% 6.0 Print the Solution
%--------------------------------------------------------------------------
if strcmp(printSolution, 'true')
    fprintf(' Solution: Temperature Vector\n');
    fprintf('------------------------------------------------\n');
    fprintf('T vector:\n')
    for i = 1:nCells
       fprintf('%10.6f\n', Tvector(i)); 
    end
    fprintf('\n')
    fprintf('------------------------------------------------\n')
end

%--------------------------------------------------------------------------
% 7.0 Plot the solution
%--------------------------------------------------------------------------

% Plot the data if desired
if strcmp(plotOutput,'true')

    fprintf(' Plotting ...\n')
    fprintf('------------------------------------------------\n')
    
    % Append the boundary temperature values to the vector, so we can
    % plot the complete solution
    xPlotting = [xFaces(1), xCentroids, xFaces(end)];
    temperaturePlotting = [tempLeft; Tvector; tempRight];

    % Figure Size Parameters
    figSizeXcm = 8.5;
    aspectRatio = 4.0/3.0;
    figSizeYcm = figSizeXcm / aspectRatio;
    figSizeXpixels = figSizeXcm * 37.79527559055118;
    figSizeYpixels = figSizeYcm * 37.79527559055118;

    % Figure font, text and line widths
    fontSize = 10;
    fontChoice = 'Arial';
    lineWidth = 1.0;
    markerSize = 4;
    
    % Colours for the line plots
    colour1 = 'black';
    colour2 = [0.0, 0.129, 0.2784];

    % Adjust anchor for where figure shows up on screen (px)
    x0 = 100;
    y0 = 100;

    fig1 = figure('Name', '1D Diffusion');
    box on;
    hold on;
    plot(xPlotting, temperaturePlotting, 'k-o', 'Color', colour2, ...
        'MarkerSize', markerSize, 'linewidth', lineWidth + 0.2);
    hold off;
    xlabel('x [m]', 'FontSize', fontSize)
    ylabel('T [^{\circ} C]', 'FontSize', fontSize)
    grid on;
    set(gca, 'fontsize', fontSize);
    set(gca, 'linewidth', lineWidth);
    set(gcf, 'position', [x0, y0, figSizeXpixels, figSizeYpixels]);
    legend({'CFD'}, 'NumColumns', 1, 'Location', 'Best')
    
end

%==========================================================================
% END OF FILE
%==========================================================================