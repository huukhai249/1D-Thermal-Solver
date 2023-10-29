#include "solveM.h"
solveM::solveM(parameters &p)
{
    m_InputParameter = p;
    m_Matrix = {};
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
    for (int i = 0; i < m_InputParameter.getnCells(); i++)
    {
        n_row.push_back(0);
    }
    for (int j = 0; j < m_InputParameter.getnCells(); j++)
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
    /*===================== @ for convecion - diffusion terms only =================

        -- Interior cells --
            aL = Dl*Al + Fl/2
            aR = Dr*Ar - Fl/2
            Sp = 0; Su = HS*V

        -- Boundary cells --
            aL_left = 0;                         aL_right = Dr*Ar + Fr/2
            aR_left = Dr*Ar - Fr/2;              aR_right = 0;
            Sp_left = -(2DlAl+Fl);               Sp_right = -(2DrAr-Fr)
            Su_left = TA*(2DlAl+Fl) + HS*V;      Su_right = TB*(2DrAr-Fr) + HS*V
                            aP = aL + aR + (Fr-Fl) - Sp
                            where D = k/d; F = rho*Cp*U*A
    ===============================================================================*/
    // Calculating the cell length -- this is also distance between cell's centroid
    double Lcell = m_InputParameter.getBarLength() / m_InputParameter.getnCells();
    // calc materials properties
    double DA = static_cast<double>(m_InputParameter.getThermalConductivity() * m_InputParameter.getArea() / Lcell);
    // convection coeficients, for Ar=Af -> Fr= Fl = F
    double F = m_InputParameter.getRho() * m_InputParameter.getCp() * m_InputParameter.getVelocity() * m_InputParameter.getArea();
    // Heat Source
    double HS = m_InputParameter.getheatSourcePerVol() * m_InputParameter.getArea() * Lcell;
    double aL_left = 0;
    double aR_left = DA - F / 2;
    double Sp_left = -(2 * DA + F);
    double aP_left = aL_left + aR_left - Sp_left;
    // boundary left
    m_Matrix.at(0).at(0) = aP_left;
    m_Matrix.at(0).at(1) = -aR_left;
    // interior indices
    double aL_interior = DA + F / 2;
    double aR_interior = DA - F / 2;
    double Sp_interior = 0;
    double aP_interior = aL_interior + aR_interior - Sp_interior;
    int index_x = 1, index_y = 1;
    while (index_y < m_InputParameter.getnCells() - 1)
    {
        m_Matrix.at(index_y).at(index_x - 1) = -aL_interior;
        m_Matrix.at(index_y).at(index_x) = aP_interior;
        m_Matrix.at(index_y).at(index_x + 1) = -aR_interior;
        index_x++;
        index_y++;
    }
    // boundary right
    double aL_right = DA + F / 2;
    double aR_right = 0;
    double Sp_right = -(2 * DA - F);
    double aP_right = aL_right + aR_right - Sp_right;
    m_Matrix.at(m_InputParameter.getnCells() - 1).at(m_InputParameter.getnCells() - 1) = aP_right;
    m_Matrix.at(m_InputParameter.getnCells() - 1).at(m_InputParameter.getnCells() - 2) = -aL_right;
    for(int i=0; i<m_InputParameter.getnCells(); i++){
        for(int j=0; j<m_InputParameter.getnCells(); j++){
            std::cout<<m_Matrix.at(i).at(j)<<" ";
        }
        std::cout<<"\n";
    }
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-       Calculating Source Term       -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    // Boundary Left
    m_Source_Terms.push_back(m_InputParameter.getTempLeft() * (2 * DA + F) + HS);
    // Interior cells
    for (int i = 1; i < m_InputParameter.getnCells() - 1; i++)
    {
        m_Source_Terms.push_back(HS);
    }
    // Boundary right
    m_Source_Terms.push_back(m_InputParameter.getTempRight() * (2 * DA - F) + HS);
}

std::vector<double> solveM::getSolution() const
{
    return m_Solutions;
}

void solveM::solveMatrix(vector<vector<double>> A, vector<double> b)
{
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-              solveMatrix            -" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    try
    {
     //
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
    std::cout<<"hhahhahah"<<endl;
    for(int i=0; i<m_InputParameter.getnCells(); i++){
        for(int j=0; j<m_InputParameter.getnCells(); j++){
            std::cout<<m_Matrix.at(i).at(j)<<" ";
        }
        std::cout<<"\n";
    }
    solveMatrix(m_Matrix, m_Source_Terms);
    std::cout << "Done." << std::endl;
}
