#pragma once
#include <iostream>
#include <vector>
class parameters
{
    private:
    // Thermal Conductivity of the bar (W/mK)
    double k;
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
    // RHO
    double rho;
    // Heat capaciry Cp
    double Cp;
    // velocity for 1-Dimesion
    double U;

public:  
 //getter-setter func
    double getThermalConductivity() const;
    void setThermalConductivity(const double& ther); 

    double getArea() const;
    void setArea(const double& ther); 
    
    double getBarLength() const;
    void setBarLength(const double& ther); 
    
    double getnCells() const;
    void setnCells(const double& ther); 
    
    double getTempRight() const;
    void setTempRight(const double& ther); 

    double getTempLeft() const;
    void settempLeft(const double& ther); 

    double getheatSourcePerVol() const;
    void setheatSourcePerVol(const double& ther); 

    double getRho() const;
    void setRho(const double& ther); 

    double getCp() const;
    void setCp(const double& ther); 

    double getVelocity() const;
    void setVelocity(const double& ther); 
    // Reading parameters
    void readingDiffusionOnly();
    void readingDiffusion_ConvectionPara();
    void readingParameters();
    parameters();
};
