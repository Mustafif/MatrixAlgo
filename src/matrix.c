#include "../includes/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

//we assume square matrices throughout this program. 
//assume dimensions always agree

Matrix1 __M1_new(int rows, int cols)
{
    Matrix1 matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = (T **)malloc(rows * sizeof(T *));
    for (int i = 0; i < rows; i++)
    {
        matrix.data[i] = (T *)calloc(cols, sizeof(T));
    }
    return matrix;
}

void __M1_free(Matrix1 *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        free(matrix->data[i]);
    }
    free(matrix->data);
}

void __M1_print(Matrix1 matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            printf("%f ", matrix.data[i][j]);
        }
        printf("\n");
    }
}

Matrix1 __M1_identity(int n)
{
    Matrix1 matrix = __M1_new(n, n);
    for (int i = 0; i < n; i++)
    {
        matrix.data[i][i] = 1;
    }
    return matrix;
}

Matrix1 __M1_setRow(Matrix1 matrix, int row, T *values)
{
    for (int i = 0; i < matrix.cols; i++)
    {
        matrix.data[row][i] = values[i];
    }
    return matrix;
}

Matrix1 __M1_setCol(Matrix1 matrix, int col, T *values)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        matrix.data[i][col] = values[i];
    }
    return matrix;
}

Matrix1 __M1_set(Matrix1 matrix, int row, int col, T value)
{
    matrix.data[row][col] = value;
    return matrix;
}

T __M1_get(Matrix1 matrix, int row, int col)
{
    return matrix.data[row][col];
}

T *__M1_getRow(Matrix1 matrix, int row)
{
    return matrix.data[row];
}

T *__M1_getCol(Matrix1 matrix, int col)
{
    T *values = (T *)malloc(matrix.rows * sizeof(T));
    for (int i = 0; i < matrix.rows; i++)
    {
        values[i] = matrix.data[i][col];
    }
    return values;
}

// Improvements that can be made:
// - Parallelize the addition operation
// - Use SIMD Operations to speed up the addition operation
// - Unroll the loops to reduce the loop overhead
//Matrix1 __M1_add(Matrix1 const A, Matrix1 const B)
//{
//    if (A.rows != B.rows || A.cols != B.cols) {
//        fprintf(stderr, "Invalid Dimensions");
//        exit(1);
//    }
//    Matrix1 result = __M1_new(A.rows, A.cols);
//    if (A.cols < A.rows) {
//        //SIMD operation on column vectors
//    }
//    //SIMD operation on row vectors
//    for (int i = 0; i < A.rows; i++)
//    {
//        for (int j = 0; j < A.cols; j++)
//        {
//            result.data[i][j] = A.data[i][j] + B.data[i][j];
//        }
//    }
//    return result;
//}

Matrix1 __M1_sub(Matrix1 const A, Matrix1 const B) 
{
    if (A.rows != B.rows || A.cols != B.cols) {
        fprintf(stderr, "Invalid Dimensions");
        exit(1);
    }
    Matrix1 result = __M1_new(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i][j] = A.data[i][j] - B.data[i][j];
        }
    }
    return result;
}

Matrix1 __M1_mulScalar(Matrix1 matrix, T scalar) 
{
    Matrix1 result = __M1_new(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            result.data[i][j] = scalar * matrix.data[i][j];
        }
    }
    return result;
}

Matrix1 __M1_mmul(Matrix1 const A, Matrix1 const B)
{
    if(A.cols != B.rows) {
        fprintf(stderr, "Invalid dimensions");
        exit(1);
    }
    Matrix1 C = __M1_new(A.rows, B.cols);
    for(int row = 0; row < A.rows; row++)
        for(int col = 0; col < B.cols; col++)
            for(int idx = 0; idx < A.cols; idx++)
                C.data[row][col] += A.data[row][idx] * B.data[idx][col];
    return C;
}

Matrix1 __M1_transpose(Matrix1 matrix)
{
    Matrix1 result = __M1_new(matrix.cols, matrix.rows);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            result.data[i][j] = matrix.data[j][i];
        }
    }
    return result;
}

//recursive approach
//T __M1_determinant(Matrix1 matrix) 
//{
//    T result;
//    if (matrix.rows != matrix.cols) {
//        fprintf(stderr, "Matrix must be square")
//        exit(1);
//    }

//    //find determinant
//    if (matrix.rows = 1) {
//        result = __M1_get(matrix, 0, 0);
//        return result;
//    }
//    elif (__M1_isDiagonal(matrix) || 
//        __M1_isTriangular(matrix))  
//    {
//        for (int d = 0; d < matrix.cols; d++) {
//            result = result * matrix.data[i][i];
//        }
//        return result;
//    }
//    elif (//matrix has LU factorization
//    false) {//call *__M1_LU. determinant of product is product of determinants}
//    for (int col = 0; col < matrix.cols; col++) {
//    }
//} 

int __M1_isDiagonal(Matrix1 matrix) {
    if (matrix.rows != matrix.cols) {
        return 0;
    }
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            if (i != j) {
                if (matrix.data[i][j] != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

//int __M1_isTriangular(Matrix1 matrix) {}



//still trying to figure this out ) :
void __M1_delRow(Matrix1 *matrix, int row) 
{
    if (row >= matrix->rows || row < 0) {
        fprintf(stderr, "Row index is out of bounds");
        exit(1);
    }

    
    for(int i = row + 1; i < matrix->rows; i++) {
        matrix->data[i-1] = matrix->data[i];
    }

    //update number of rows
    matrix->rows--;

    //deallocate memory
    free(matrix->data[row]);
}

// Matrix1 __M1_delCol(Matrix1 matrix, int col) {}

// Matrix1 __M1_inverse(Matrix1 matrix) {}

// int __M1_rank(Matrix1 matrix) {}

T __M1_trace(Matrix1 matrix) 
{
    T result = (T)0;
    for (int i = 0; i < matrix.cols; i++) 
    {
        result = result + matrix.data[i][i];
    }
    return result;
}

// T *__M1_eigenvalues(Matrix1 matrix) {}

// Matrix1 __M1_eigenvectors(Matrix1 matrix) {}

// Matrix1 *__M1_LU(Matrix1 matrix) {}

static void __M1_partialPivot(Matrix1 matrix, int row, int col)
{
    int maxRow = row;
    for (int i = row + 1; i < matrix.rows; i++)
    {
        if (matrix.data[i][col] > matrix.data[maxRow][col])
        {
            maxRow = i;
        }
    }
    if (maxRow != row)
    {
        T *temp = matrix.data[row];
        matrix.data[row] = matrix.data[maxRow];
        matrix.data[maxRow] = temp;
    }
}

// Matrix1 __M1_rref(Matrix1 matrix) {}
t
// T *__M1_solve(Matrix1 matrix, T *b) {}

//////////////////////////////////////////////////////////////////////
///////////////////////// Matrix 2 ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Matrix2 __M2_new(int rows, int cols) {}

// Matrix2 __M2_free(Matrix2 *matrix) {}

// void __M2_print(Matrix2 matrix) {}

// Matrix2 __M2_identity(int n) {}

// Matrix2 __M2_setRow(Matrix2 matrix, int row, T *values) {}

// Matrix2 __M2_setCol(Matrix2 matrix, int col, T *values) {}

// Matrix2 __M2_set(Matrix2 matrix, int row, int col, T value) {}

// T __M2_get(Matrix2 matrix, int row, int col) {}

// T *__M2_getRow(Matrix2 matrix, int row) {}

// T *__M2_getCol(Matrix2 matrix, int col) {}

// Matrix2 __M2_add(Matrix2 const A, Matrix2 const B) {}

// Matrix2 __M2_sub(Matrix2 const A, Matrix2 const B) {}

// Matrix2 __M2_mulScalar(Matrix2 matrix, T scalar) {}

// Matrix2 __M2_mmul(Matrix2 const A, Matrix2 const B) {}

// Matrix2 __M2_transpose(Matrix2 matrix) {}

// T __M2_determinant(Matrix2 matrix) {}

// Matrix2 __M2_inverse(Matrix2 matrix) {}

// int __M2_rank(Matrix2 matrix) {}

// T __M2_trace(Matrix2 matrix) {}

// T *__M2_eigenvalues(Matrix2 matrix) {}

// Matrix2 __M2_eigenvectors(Matrix2 matrix) {}

// Matrix2 *__M2_LU(Matrix2 matrix) {}

static void __M2_partialPivot(Matrix2 matrix, int row, int col)
{
    int maxRow = row;
    for (int i = row + 1; i < matrix.rows; i++)
    {
        if ((matrix.data[i] + col) > (matrix.data[maxRow] + col))
        {
            maxRow = i;
        }
    }
    if (maxRow != row)
    {
        double temp = matrix.data[row];
        matrix.data[row] = matrix.data[maxRow];
        matrix.data[maxRow] = temp;
    }
}

// Matrix2 __M2_rref(Matrix2 matrix) {}

// T *__M2_solve(Matrix2 matrix, T *b) {}