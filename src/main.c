#include <stdio.h>
#include <time.h>
#include <matrix.h>
#include <stdlib.h>


int main()
{
    Matrix1 matrix = __M1_new(3, 3);
    Matrix1 matrix_2 = __M1_identity(2);
    
    T nums[] = {2.093,10.090,0.0918};
    T nums2[] = {0,3.1415,2.9714};
    T nums3[] = {-11, 3};
    __M1_setCol(matrix, 0, nums);
    __M1_setCol(matrix, 2, nums2);
    __M1_setRow(matrix_2, 0, nums3);

    //testing multiply by scalar and subtraction functions
    Matrix1 matrix_3 = __M1_add(matrix, matrix_2);
    Matrix1 matrix_4 = __M1_mmul(matrix, matrix_2);
    T mytrace = __M1_trace(matrix);

    //output matrices
    printf("Matrix:\n");
    __M1_print(matrix);
    printf("Matrix_2:\n");
    __M1_print(matrix_2);
    printf("Matrix_3:\n");
    __M1_print(matrix_3);
    printf("matrix_4:\n");
    __M1_print(matrix_4);
    printf("%f", mytrace);

    //deallocate memory
    __M1_free(&matrix);
    __M1_free(&matrix_2);
    __M1_free(&matrix_3);
    __M1_free(&matrix_4);
    return 0;
}
