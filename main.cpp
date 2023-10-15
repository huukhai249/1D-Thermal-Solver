#include "parameters.h"
#include "solveM.h"

int main()
{
    parameters p1;
    p1.readingParameters();
    solveM s(p1);
    s.solve();
    std::vector<double> solutions = s.getSolution();

    for (int i = 0; i < solutions.size(); i++)
    {
        std::cout << solutions.at(i) << endl;
    }
    return 0;
}