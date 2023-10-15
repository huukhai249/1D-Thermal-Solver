#pragma once
#include <iostream>
class parameters
{
public:
    // Thermal Conductivity of the bar (W/mK)
    double thermalCond;
    // Cross-sectional Area of the bar (m2)
    double area;
    // Length of the bar (m)
    double barLength;
    // Number of cells in the mesh
    double nCells;
    //   Temperature at the left hand side of the bar (deg C)
    double tempLeft;
    // Temperature at the left hand side of the bar (deg C)
    double tempRight;
    // Heat source per unit volume (W/m3)
    double heatSourcePerVol;
    
    void readingParameters();
};
