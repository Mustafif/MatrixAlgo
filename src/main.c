#include <stdio.h>
#include <time.h>
#include <matrix.h>
int main()
{
    Matrix1 A = __M1_identity(1000);
    Matrix1 B = __M1_identity(1000);

    clock_t start = clock();
    Matrix1 C = __M1_add(A, B);
    __M1_print(C);
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);

    __M1_free(&A);
    __M1_free(&B);
    return 0;
}