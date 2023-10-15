#include "solveM.h"
#include "linearSolving.h"

solveM::solveM(parameters &p)
{
    m_InputParameter = p;
    m_Matrix = {};
    L_Matrix = {};

    m_Source_Terms = {};
    std::cout << "================================================" << std::endl;
    std::cout << "            solve_1D_DiffusionEquation          " << std::endl;
    std::cout << "================================================" << std::endl;
}

void solveM::createMesh()
{
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "             Creating Mesh             " << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::vector<double> n_row;
    for (int i = 0; i < m_InputParameter.nCells; i++)
    {
        n_row.push_back(0);
    }
    for (int j = 0; j < m_InputParameter.nCells; j++)
    {
        m_Matrix.push_back(n_row);
    }
    std::cout << "Create mesh done." << std::endl;
}
void solveM::calcParameter()
{
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-    Calculating Matrix Coefficients  -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    // Calculating the cell length -- this is also distance between cell's centroid
    double Lcell = m_InputParameter.barLength / m_InputParameter.nCells;
    // calc materials properties
    double DA = static_cast<double>(m_InputParameter.thermalCond * m_InputParameter.area / Lcell);
    // Heat Source
    double HS = m_InputParameter.heatSourcePerVol * m_InputParameter.area * Lcell;
    // boundary left
    m_Matrix.at(0).at(0) = DA + 0 + 2 * DA;
    m_Matrix.at(0).at(1) = -DA;
    // interior indices
    int index_x = 1, index_y = 1;
    while (index_y < m_InputParameter.nCells - 1)
    {
        m_Matrix.at(index_y).at(index_x - 1) = -DA;
        m_Matrix.at(index_y).at(index_x) = 2 * DA;
        m_Matrix.at(index_y).at(index_x + 1) = -DA;
        index_x++;
        index_y++;
    }
    // boundary right
    m_Matrix.at(m_InputParameter.nCells - 1).at(m_InputParameter.nCells - 2) = -DA;
    m_Matrix.at(m_InputParameter.nCells - 1).at(m_InputParameter.nCells - 1) = DA + 0 + 2 * DA;

    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-       Calculating Source Term       -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    m_Source_Terms.push_back(m_InputParameter.tempLeft * (2 * DA) + HS);
    for (int i = 1; i < m_InputParameter.nCells - 1; i++)
    {
        m_Source_Terms.push_back(0);
    }
    m_Source_Terms.push_back(m_InputParameter.tempRight * (2 * DA) + HS);
}

std::vector<double> solveM::getSolution() const
{
    return m_Solutions;
}

void solveM::solveMatrix(vector<vector<double>> A, vector<vector<double>> B, vector<double> b)
{
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-              solveMatrix            -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    try
    {
        InitlowerMatrixBase(B, b.size());
        decompositeMatrix(A, B, b.size());
        printMatrix(A,b.size());
        cout << "=============================="<<endl;
        printMatrix(B,b.size());
        
        // m_Solutions = solve_linear_equation(A, b);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void solveM::solve()
{
    solveM::createMesh();
    solveM::calcParameter();
    solveMatrix(m_Matrix,L_Matrix, m_Source_Terms);
    std::cout << "Done." << std::endl;
}
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-       Calculating Source Term       -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    m_Source_Terms.push_back(m_InputParameter.tempLeft*(2*DA) + HS);
    for (int i = 1; i < m_InputParameter.nCells-1; i++)
    {
        m_Source_Terms.push_back(0);
    }
    m_Source_Terms.push_back(m_InputParameter.tempRight*(2*DA) + HS);
}
