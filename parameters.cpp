#include "parameters.h"
using namespace std;
parameters::parameters() : k(0.0), area(0.0), barLength(0.0), nCells(0.0), tempLeft(0.0), tempRight(0.0), heatSourcePerVol(0.0), rho(0.0), Cp(0.0), U(0.0)
{
    cout << "Init Parameter()" << endl;
}
template <typename Input>
Input getPara()
{
    Input temp;
    cin >> temp;
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cout << "Error, Wrong input data Type. Please re-enter: ";
            std::cin.ignore();
            cin >> temp;
        }
    } while (cin.fail());
    return temp;
}
double parameters::getThermalConductivity() const
{
    return k;
}
void parameters::setThermalConductivity(const double &ther)
{
    k = ther;
}

double parameters::getArea() const
{
    return area;
}
void parameters::setArea(const double &A)
{
    area = A;
}

double parameters::getBarLength() const
{
    return barLength;
}
void parameters::setBarLength(const double &L)
{
    barLength = L;
}

int parameters::getnCells() const
{
    return nCells;
}
void parameters::setnCells(const int &cells)
{
    nCells = cells;
}

double parameters::getTempRight() const
{
    return tempRight;
}
void parameters::setTempRight(const double &Tr)
{
    tempRight = Tr;
}

double parameters::getTempLeft() const
{
    return tempLeft;
}
void parameters::settempLeft(const double &Tl)
{
    tempLeft = Tl;
}

double parameters::getheatSourcePerVol() const
{
    return heatSourcePerVol;
}
void parameters::setheatSourcePerVol(const double &HS)
{
    heatSourcePerVol = HS;
}

double parameters::getRho() const
{
    return rho;
}
void parameters::setRho(const double &Rho)
{
    rho = Rho;
}

double parameters::getCp() const
{
    return Cp;
}
void parameters::setCp(const double &ther)
{
    Cp = ther;
}

double parameters::getVelocity() const
{
    return U;
}
void parameters::setVelocity(const double &velo)
{
    U = velo;
}
int Option()
{
    cout << "reading Diffusion Only?[y/n]" << endl;
    if (getPara<char>() != 'y')
    {
        cout << "reading Diffusion and Convection Parameter?[y/n]" << endl;
        if (getPara<char>() != 'y')
        {
            Option();
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 1;
    }
}
void parameters::readingDiffusionOnly()
{
    cout << "Reading parameters..." << endl;
    cout << "Thermal Conductivity of the bar (W/mK), k = ";
    setThermalConductivity(getPara<double>());
    cout << "Cross-sectional Area of the bar (m2), A = ";
    setArea(getPara<double>());
    cout << "Length of the bar (m), L = ";
    setBarLength(getPara<double>());
    cout << "Number of cells in the mesh, nCells = ";
    setnCells(getPara<double>());
    cout << "Temperature at the left hand side of the bar (deg C), tempLeft = ";
    settempLeft(getPara<double>());
    cout << "Temperature at the right hand side of the bar (deg C), tempRight = ";
    setTempRight(getPara<double>());
    cout << "Heat source per unit volume (W/m3), H = ";
    setheatSourcePerVol(getPara<double>());
}
void parameters::readingDiffusion_ConvectionPara()
{
    parameters::readingDiffusionOnly();
    cout << "Rho = ";
    setRho(getPara<double>());
    cout << "Cp = ";
    setCp(getPara<double>());
    cout << "Velocity = ";
    setVelocity(getPara<double>());
}

void parameters::readingParameters()
{
    switch (Option())
    {
    case 1:
    {
        parameters::readingDiffusionOnly();
        break;
    }
    case 2:
    {
        parameters::readingDiffusion_ConvectionPara();
        break;
    }

    default:
        break;
    }
    cout << "Maximun iteration = ";
    setMaxiteration(getPara<int>());
    cout << "Tolerance = ";
    setTOL(getPara<double>());
}
int parameters::getMaxiteration() const
{
    return Niteration;
}
void parameters::setMaxiteration(const int &N)
{
    Niteration = N;
}

double parameters::getTOL() const
{
    return TOL;
}
void parameters::setTOL(const double &tolerance)
{
    TOL = tolerance;
}
