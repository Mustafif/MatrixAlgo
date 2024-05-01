#define TYPE double

//> Matrix1 represents a matrix using a pointer to a pointer to a block of memory.
//> This representation is more intuitive and easier to work with.
typedef struct
{
    int rows;
    int cols;
    TYPE **data;
} Matrix1;

// Create a new matrix with the specified number of rows and columns
Matrix1 __M1_new(int rows, int cols);
// Free the memory allocated for the matrix
void __M1_free(Matrix1 *matrix);
// Print the matrix to the console
void __M1_print(Matrix1 matrix);
// Create an identity matrix of the specified size
Matrix1 __M1_identity(int n);

// Sets the row at the specified index to the given values
Matrix1 __M1_setRow(Matrix1 matrix, int row, TYPE *values);
// Sets the column at the specified index to the given values
Matrix1 __M1_setCol(Matrix1 matrix, int col, TYPE *values);
// Sets the value at the specified row and column to the given value
Matrix1 __M1_set(Matrix1 matrix, int row, int col, TYPE value);

// Returns the value at the specified row and column
TYPE __M1_get(Matrix1 matrix, int row, int col);
// Returns the row at the specified index
TYPE *__M1_getRow(Matrix1 matrix, int row);
// Returns the column at the specified index
TYPE *__M1_getCol(Matrix1 matrix, int col);

// Add two matrices
Matrix1 __M1_add(Matrix1 const A, Matrix1 const B);
// Subtract two matrices
Matrix1 __M1_sub(Matrix1 const A, Matrix1 const B);
// Multiply a matrix by a scalar
Matrix1 __M1_mulScalar(Matrix1 matrix, TYPE scalar);
// Multiply two matrices
Matrix1 __M1_mmul(Matrix1 const A, Matrix1 const B);

// Transpose a matrix
Matrix1 __M1_transpose(Matrix1 matrix);
// Calculate the determinant of the matrix
TYPE __M1_determinant(Matrix1 matrix);
// Inverse the matrix
Matrix1 __M1_inverse(Matrix1 matrix);
// Calculate the rank of the matrix
int __M1_rank(Matrix1 matrix);
// Calculate the trace of the matrix
TYPE __M1_trace(Matrix1 matrix);
// Calculate the eigenvalues of the matrix
TYPE *__M1_eigenvalues(Matrix1 matrix);
// Calculate the eigenvectors of the matrix
Matrix1 __M1_eigenvectors(Matrix1 matrix);
// Calculate the LU decomposition of the matrix
Matrix1 *__M1_LU(Matrix1 matrix);
// Calculate the RREF of the matrix
Matrix1 __M1_rref(Matrix1 matrix);
// Solve the system of linear equations
TYPE *__M1_solve(Matrix1 matrix, TYPE *b);


//> Matrix2 represents an alternative way to represent a matrix
//> using a single pointer to a contiguous block of memory.
//> This representation is more cache-friendly and can be more efficient with time complexity.
// To access the element at row i and column j, you can use the formula:
// data[i * cols + j]
typedef struct
{
    int rows;
    int cols;
    TYPE *data;
} Matrix2;

// Create a new matrix with the specified number of rows and columns
Matrix2 __M2_new(int rows, int cols);
// Free the memory allocated for the matrix
void __M2_free(Matrix2 *matrix);
// Print the matrix to the console
void __M2_print(Matrix2 matrix);
// Create an identity matrix of the specified size
Matrix2 __M2_identity(int n);

// Sets the row at the specified index to the given values
Matrix2 __M2_setRow(Matrix2 matrix, int row, TYPE *values);
// Sets the column at the specified index to the given values
Matrix2 __M2_setCol(Matrix2 matrix, int col, TYPE *values);
// Sets the value at the specified row and column to the given value
Matrix2 __M2_set(Matrix2 matrix, int row, int col, TYPE value);

// Returns the value at the specified row and column
TYPE __M2_get(Matrix2 matrix, int row, int col);
// Returns the row at the specified index
TYPE *__M2_getRow(Matrix2 matrix, int row);
// Returns the column at the specified index
TYPE *__M2_getCol(Matrix2 matrix, int col);

// Add two matrices
Matrix2 __M2_add(Matrix2 matrix1, Matrix2 matrix2);
// Subtract two matrices
Matrix2 __M2_sub(Matrix2 matrix1, Matrix2 matrix2);
// Multiply a matrix by a scalar
Matrix2 __M2_mulScalar(Matrix2 matrix, TYPE scalar);
// Multiply two matrices
Matrix2 __M2_mmul(Matrix2 matrix1, Matrix2 matrix2);

// Transpose a matrix
Matrix2 __M2_transpose(Matrix2 matrix);
// Calculate the determinant of the matrix
TYPE __M2_determinant(Matrix2 matrix);
// Inverse the matrix
Matrix2 __M2_inverse(Matrix2 matrix);
// Calculate the rank of the matrix
int __M2_rank(Matrix2 matrix);
// Calculate the trace of the matrix
TYPE __M2_trace(Matrix2 matrix);
// Calculate the eigenvalues of the matrix
TYPE *__M2_eigenvalues(Matrix2 matrix);
// Calculate the eigenvectors of the matrix
Matrix2 __M2_eigenvectors(Matrix2 matrix);
// Calculate the LU decomposition of the matrix
Matrix2 *__M2_LU(Matrix2 matrix);
// Calculate the RREF of the matrix
Matrix2 __M2_rref(Matrix2 matrix);
// Solve the system of linear equations
TYPE *__M2_solve(Matrix2 matrix, TYPE *b);