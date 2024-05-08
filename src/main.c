#include <stdio.h>
#include <time.h>
#include <matrix.h>
#include <stdlib.h>


int main()
{
    Matrix1 matrix = __M1_new(3, 3);
    Matrix1 matrix_2 = __M1_identity(3);
    
    //creating dynamic arrays
    T* ptr;
    T* ptr_2;
    ptr = (T*)malloc(sizeof(T)*3);
    ptr_2 = (T*)malloc(sizeof(T)*3);

    if (ptr == NULL || ptr_2 == NULL) { 
        printf("Memory not allocated.\n"); 
    } 
    else { 
        // Memory allocated 
        printf("Memory successfully allocated using "
            "malloc.\n");
    }


    for (int i = 0; i < matrix.rows; ++i) {
        ptr[i] = 2.09*i;
        ptr_2[i] = -1.04*i;
    }

    //accessing dynamic array using dereferencing
    __M1_setRow(matrix, 0, ptr); 
    __M1_setRow(matrix, 2, ptr_2);

    //testing multiply by scalar and subtraction functions
    Matrix1 matrix_3 = __M1_mulScalar(__M1_sub(matrix_2, matrix), 3.14);
    Matrix1 matrix_4 = __M1_mmul(matrix, matrix_2);

    //output matrices
    printf("Matrix:\n");
    __M1_print(matrix);
    printf("Matrix_2:\n");
    __M1_print(matrix_2);
    printf("Matrix_3:\n");
    __M1_print(matrix_3);
    printf("matrix_4:\n");
    __M1_print(matrix_4);

    //deallocate memory
    __M1_free(&matrix);
    __M1_free(&matrix_2);
    __M1_free(&matrix_3);
    __M1_free(&matrix_4);
    free(ptr);
    free(ptr_2);
    return 0;
}
