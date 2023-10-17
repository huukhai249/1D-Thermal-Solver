#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Test the matrix is invertible (A != A_-1)
bool is_invertible(vector<vector<double>> &A)
{
    double det = 1;
    for (int i = 0; i < A.size(); i++)
    {
        det *= A[i][i];
    }
    return det != 0;
}
// create lower matrix base
void InitlowerMatrixBase(vector<vector<double>> &L_matrix, int size)
{
    std::vector<double> n_row;
    for (int i = 0; i < size; i++)
    {
        n_row.push_back(0);
    }
    for (int j = 0; j < size; j++)
    {
        L_matrix.push_back(n_row);
    }
}
/// This step will decomposite square matric A = L*U. This often called Lower-Upper method to solve linear equation.
bool decompositeMatrix(vector<vector<double>> &Matrix, vector<vector<double>> &L_Matrix, int rowsize)
{
    int step_ = 0;

    while (step_ < rowsize - 1)
    {
        int row = step_ + 1;
        int count = 0;
        for (int idx = row; idx < rowsize; idx++)
        {
            L_Matrix.at(idx).at(step_) = Matrix.at(idx).at(step_) / Matrix.at(step_).at(step_);
            count++;

            for (int index = 0; index < rowsize - 1; index++)
            {
                Matrix.at(idx).at(index) = Matrix.at(idx).at(index) - L_Matrix.at(idx).at(step_) * Matrix.at(idx - count).at(index);
            }
            if (!is_invertible(Matrix))
            {
                std::cout << " This is singular matrix" << endl;
                return false;
            }
        }
        step_++;
    }
    return true;
}
void printMatrix(vector<vector<double>> &Matrix, int rowsize)
{
    for (int i = 0; i < rowsize; i++)
    {
        for (int j = 0; j < rowsize; j++)
        {
            cout << Matrix.at(i).at(j) << "   ";
        }
        cout << "\n";
    }
}