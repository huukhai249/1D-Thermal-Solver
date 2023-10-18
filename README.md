# 1D-Thermal-Solver
This is a 1D thermal solver using C++ code based on the finite volume method. 
![Themal](https://github.com/huukhai249/1D-Thermal-Solver/assets/63088885/0a2f3c50-6975-45c5-b3f8-1acb7a663914)

**Example 1:** Only convection - diffusion terms in 1D governed by equation: 

    grad*(rho*Cp*U*T) = grad*(k*grad(T)) + S

Other conditions like the figure below:

![Example1](https://github.com/huukhai249/1D-Thermal-Solver/assets/63088885/06a4670e-1453-4db4-89e7-f5e02a41265a)

The Gauss–Seidel method is an iterative technique for solving a square system of n (n=3) linear equations with unknown x.
Given Ax=B, to find the system of equation x which satisfies this condition.
In more detail, A, x, and b in their components are :
![1122](https://github.com/huukhai249/1D-Thermal-Solver/assets/63088885/68e00227-b2fa-4329-9805-e162961a7379)
Thus, the general solution of equation Ax = b obeys:
![1234](https://github.com/huukhai249/1D-Thermal-Solver/assets/63088885/ac81c5ad-56d1-49fe-82fa-32c2d3ceef58)
