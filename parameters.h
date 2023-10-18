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
    int nCells;
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
    // tolerance
    double TOL;
    // maximum number of iterations
    int Niteration;

public:
    // getter-setter func
    double getThermalConductivity() const;
    void setThermalConductivity(const double &ther);

    double getArea() const;
    void setArea(const double &area);

    double getBarLength() const;
    void setBarLength(const double &L);

    int getnCells() const;
    void setnCells(const int &cells);

    double getTempRight() const;
    void setTempRight(const double &tempR);

    double getTempLeft() const;
    void settempLeft(const double &tempL);

    double getheatSourcePerVol() const;
    void setheatSourcePerVol(const double &Hs);

    double getRho() const;
    void setRho(const double &rho);

    double getCp() const;
    void setCp(const double &cp);

    double getVelocity() const;
    void setVelocity(const double &V);

    int getMaxiteration() const;
    void setMaxiteration(const int &N);

    double getTOL() const;
    void setTOL(const double &tol);

    // Reading parameters
    void readingDiffusionOnly();
    void readingDiffusion_ConvectionPara();
    void readingParameters();
    parameters();
};
