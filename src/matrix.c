#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>


Matrix1 __M1_new(int rows, int cols)
{
    Matrix1 matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix.data[i] = (double *)malloc(cols * sizeof(double));
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

Matrix1 __M1_setRow(Matrix1 matrix, int row, double *values)
{
    for (int i = 0; i < matrix.cols; i++)
    {
        matrix.data[row][i] = values[i];
    }
    return matrix;
}

Matrix1 __M1_setCol(Matrix1 matrix, int col, double *values)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        matrix.data[i][col] = values[i];
    }
    return matrix;
}

Matrix1 __M1_set(Matrix1 matrix, int row, int col, double value)
{
    matrix.data[row][col] = value;
    return matrix;
}

double __M1_get(Matrix1 matrix, int row, int col)
{
    return matrix.data[row][col];
}

double *__M1_getRow(Matrix1 matrix, int row)
{
    return matrix.data[row];
}

double *__M1_getCol(Matrix1 matrix, int col)
{
    double *values = (double *)malloc(matrix.rows * sizeof(double));
    for (int i = 0; i < matrix.rows; i++)
    {
        values[i] = matrix.data[i][col];
    }
    return values;
}

// Improvements that can be made:
// - Parallelize the addition operation
// - Use SIMD instructions to speed up the addition operation
// - Check if the matrices have the same dimensions
// - Unroll the loops to reduce the loop overhead
Matrix1 __M1_add(Matrix1 const A, Matrix1 const B)
{
    Matrix1 result = __M1_new(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
    return result;
}

Matrix1 __M1_transpose(Matrix1 matrix)
{
    Matrix1 result = __M1_new(matrix.cols, matrix.rows);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            result.data[j][i] = matrix.data[i][j];
        }
    }
    return result;
}