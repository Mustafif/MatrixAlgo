#include <stdio.h>
#include <time.h>
#include <matrix.h>
#include <stdlib.h>


int main()
{
    //initializing matrices
    Matrix1 matrix = __M1_identity(3);
    T nums[] = {2, 1, 3};
    __M1_setCol(matrix, 1, nums);

    //output to terminal matrices
    printf("original matrix:\n");
    __M1_print(matrix);
    __M1_delRow(&matrix, 0);
    printf("new matrix:\n");
    __M1_print(matrix);
    
    printf("%d", __M1_isDiagonal(matrix));
    //deallocate memory
    __M1_free(&matrix);
    return 0;
}
