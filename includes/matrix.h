//> Matrix1 represents a matrix using a pointer to a pointer to a block of memory.
//> This representation is more intuitive and easier to work with.
typedef struct
{
    int rows;
    int cols;
    double **data;
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
Matrix1 __M1_setRow(Matrix1 matrix, int row, double *values);
// Sets the column at the specified index to the given values
Matrix1 __M1_setCol(Matrix1 matrix, int col, double *values);
// Sets the value at the specified row and column to the given value
Matrix1 __M1_set(Matrix1 matrix, int row, int col, double value);

// Returns the value at the specified row and column
double __M1_get(Matrix1 matrix, int row, int col);
// Returns the row at the specified index
double *__M1_getRow(Matrix1 matrix, int row);
// Returns the column at the specified index
double *__M1_getCol(Matrix1 matrix, int col);

// Add two matrices
Matrix1 __M1_add(Matrix1 matrix1, Matrix1 matrix2);
// Knowing how to add, you can do all the rest of the operations...


// Transpose a matrix
Matrix1 __M1_transpose(Matrix1 matrix);
// Inverse the matrix
Matrix1 __M1_inverse(Matrix1 matrix);
// Calculate the determinant of the matrix
double __M1_determinant(Matrix1 matrix);
// Calculate the rank of the matrix
int __M1_rank(Matrix1 matrix);
// Solve the system of linear equations
double *__M1_solve(Matrix1 matrix, double *b);



//> Matrix2 represents an alternative way to represent a matrix
//> using a single pointer to a contiguous block of memory.
//> This representation is more cache-friendly and can be more efficient with time complexity.
// To access the element at row i and column j, you can use the formula:
// data[i * cols + j]
typedef struct
{
    int rows;
    int cols;
    double *data;
} Matrix2;

Matrix2 create_matrix2(int rows, int cols);
void free_matrix2(Matrix2 *matrix);