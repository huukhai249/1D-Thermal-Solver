#include "linearSolving.h"
#include "parameters.h"
#include <math.h>
linearSolving::linearSolving(parameters &p)
{
    paramInput = std::make_shared<parameters>(p);
    std::cout << "Init linearSolving" << std::endl;
}

linearSolving::~linearSolving()
{
}
std::vector<double> initZeroVector(int vectorSize)
{
    std::vector<double> v;
    for (int i = 0; i < vectorSize; i++)
    {
        v.push_back(0);
    }
    return v;
}
// Test the matrix is singular matric (A != A_-1)
bool linearSolving::is_invertible(std::vector<std::vector<double>> A)
{
    double det = 1;
    for (int i = 0; i < A.size(); i++)
    {
        det *= A[i][i];
    }
    return det != 0;
}

double linearSolving::sigma(int start, int end, std::vector<double> a, std::vector<double> x)
{
    if (start == end)
        return 0;
    else
    {
        double SUM = 0.0;
        for (int i = start; i <= end; i++)
        {
            SUM = SUM + a.at(i) * x.at(i);
        }
        return SUM;
    }
}
std::vector<double> linearSolving::gausee_seidel_solving(std::vector<std::vector<double>> Aij, std::vector<double> b)
{
    std::cout << "================= Start program =======================" << std::endl
              << paramInput->getMaxiteration();
    // To store solution in this iterior
    std::vector<double> current_solution = initZeroVector(paramInput->getnCells());
    // To store solution at previous iterior
    std::vector<double> pre_solution = initZeroVector(paramInput->getnCells());
    int interior = 1;

    while (interior <= paramInput->getMaxiteration())
    {
        std::cout << "===========================#Iterior " << interior << "===============================" << std::endl;
        std::vector<double> TOLERANCE;
        int curentRowIdx = 0;
        while (curentRowIdx < paramInput->getnCells())
        {
            std::vector<double> currentRow = Aij.at(curentRowIdx);
            pre_solution = current_solution;
            current_solution.at(curentRowIdx) = 1 / (Aij.at(curentRowIdx).at(curentRowIdx)) * (-sigma(0, curentRowIdx - 2, currentRow, current_solution) - sigma(curentRowIdx + 1, paramInput->getnCells() - 1, currentRow, pre_solution) + b.at(curentRowIdx));
            double err = std::abs((current_solution.at(curentRowIdx) - pre_solution.at(curentRowIdx)) * (1 / current_solution.at(curentRowIdx))) * 100;
            TOLERANCE.push_back(err);
            std::cout << "*            X[" << curentRowIdx << "] = " << current_solution.at(curentRowIdx) << ", tolerance " << err << "%         " << std::endl;
            curentRowIdx++;
        }

        auto mean = [](std::vector<double> v)
        {
            double SUM = 0;
            for (unsigned long i = 0; i < v.size(); i++)
            {

                SUM = SUM + v.at(i);
            }
            return static_cast<double>(SUM / v.size());
        };

        if (mean(TOLERANCE) < paramInput->getTOL())
        {
            std::cout << "================= End. =======================" << std::endl;
            return current_solution;
        }
        interior++;
    }
    std::cout << "================= End. =======================" << std::endl;
    return current_solution;
}