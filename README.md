# Matrix Algorithms

The repository contains the implementation of Matrices in C and will follow two approaches:

1. **Using 2D Arrays**: The matrix uses a double pointer and is more intuitive to use.
2. **Using a Single Array**: The matrix uses a single pointer and is more memory efficient.

The repository will contain the following operations:

1. **Matrix Addition**
2. **Matrix Subtraction**
3. **Matrix Multiplication**
4. **Scalar Matrix Multiplication**
5. **Transposition**
6. **Determinant**
7. **Inverse**
8. **Rank**
9. **Trace**
10. **Eigenvalues and Eigenvectors**
11. **LU Decomposition**
12. **RREF**
13. **Solving Linear Equations**

The goal is to be able to port this to the MufiZ project, but also provide this as a standalone library, 
for anyone who wants to use it.


## Readings 

- [Optimizing Matrix Multiplication](https://coffeebeforearch.github.io/2020/06/23/mmul.html)
- [Gaussian Elimination](https://en.wikipedia.org/wiki/Gaussian_elimination)
- [Numerical Linear Algebra](https://en.wikipedia.org/wiki/Numerical_linear_algebra)
- [LU Decomposition](https://en.wikipedia.org/wiki/LU_decomposition)

> When computing RREF, to keep numerical stability we will need to use the method of 
> partial pivoting. 