////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Numerical Algorithm of Gauss-Seidel Method
//       Gauss-Seidel is an interative method whereas the values of the variables are modified as soon as new value is evaluated.
//       For instance, in Jacobi method the value of xi(k) is not modified until the (k + 1)th iteration but in Gauss-Seidel method
//       the value of xi(k) changes in in kth iteration only.
//
//    Author: HuuKhai-Nguyen
//    Email: Khaikn249@gmail.com
//    Web  : https://www.simtec.com
//    LinkedIn: https://www.linkedin.com/in/khai-nguyen-741b2519a/
//    Facebook: https://www.facebook.com/khai.nguyenhuu.16
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    This methos is used to solve the set of linear algebra equation: Ax = b.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <vector>
#include <memory>
class parameters;
class linearSolving
{
private:
    std::shared_ptr<parameters> paramInput;

public:
    bool is_invertible(std::vector<std::vector<double>> A);
    double sigma(int start, int end, std::vector<double> a, std::vector<double> x);
    std::vector<double> gausee_seidel_solving(std::vector<std::vector<double>> Aij, std::vector<double> b);
    void solve();
    linearSolving(parameters &p);
    ~linearSolving();
};
