#include "parameters.h"
#include <vector>
using namespace std;

class solveM
{
private:
    parameters m_InputParameter;
    std::vector<std::vector<double>> m_Matrix; 
    std::vector<std::vector<double>> L_Matrix; 
    std::vector<double> m_Source_Terms;
    std::vector<double> m_Solutions;
public:
    solveM(parameters &p);
    std::vector<double> getSolution() const;
    void createMesh();
    void calcParameter();
    void solveMatrix(vector<vector<double>> A, vector<vector<double>> B, vector<double> b);
    void solve();
};
