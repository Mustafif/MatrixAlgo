#include <stdio.h>
#include <time.h>
#include <matrix.h>
int main()
{
    Matrix1 matrix = __M1_new(3, 3);
    printf("Matrix:\n");
    __M1_print(matrix);
    return 0;
}