#pragma once
#include "parameters.h"
#include <vector>
class solveM
{
private:
    parameters m_InputParameter;
    std::vector<std::vector<double>> m_Matrix; 
    std::vector<double> m_Source_Terms;
public:
    solveM(parameters &p);
    void createMesh();
    void calcParameter();
};
