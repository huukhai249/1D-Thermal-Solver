#include "parameters.h"
using namespace std;
void getPara(double &temp)
{
    cin >> temp;
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cout << "Error, that's not a decimal number. Please reenter: ";
            std::cin.ignore();
            cin >> temp;
        }
    } while (cin.fail());
}

void parameters::readingParameters()
{
    cout << "Reading parameters..." << endl;
    cout << "Thermal Conductivity of the bar (W/mK), k = ";
    getPara(thermalCond);
    cout << "Cross-sectional Area of the bar (m2), A = ";
    getPara(area);
    cout << "Length of the bar (m), L = ";
    getPara(barLength);
    cout << "Number of cells in the mesh, nCells = ";
    getPara(nCells);
    cout << "Temperature at the left hand side of the bar (deg C), tempLeft = ";
    getPara(tempLeft);
    cout << "Temperature at the right hand side of the bar (deg C), tempRight = ";
    getPara(tempRight);
    cout << "Heat source per unit volume (W/m3), H = ";
    getPara(heatSourcePerVol);
    cout << "Completed reading parameters" << endl;

    
}
