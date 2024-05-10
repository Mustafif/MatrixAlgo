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

### MMUL Bench

In `bench.c` we created a benchmark file that will do matrix multipliciation between a 1000 x 1000 matrix, we get the following results:

```bash
# no flags
$ gcc bench.c src/matrix.c -o bench
$ ./bench
Time taken by mmul1: 4.488451 seconds
Time taken by mmul2: 2.904525 seconds
# with flags
$ gcc bench.c src/matrix.c -o bench -Wall -ffast-math -O3 -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-value
$ ./bench
Time taken by mmul1: 2.093212 seconds
Time taken by mmul2: 0.701268 seconds
```

As we can see, the second implementation can perform close to 2x better. Although, it would also be great to check other metrics such as heap usage, and
cache hitting. 