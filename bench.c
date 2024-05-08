#include "includes/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Matrix1 mmul1(Matrix1 const A, Matrix1 const B) {
   Matrix1 result = __M1_new(A.rows, A.cols);
   for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.cols; j++) {
         float nums = 0;
         for (int k = 0; k < A.cols; k++) {
            nums = nums + A.data[i][k] * B.data[k][j];
         }
         result.data[i][j] = nums;
      }
   }
   return result;
}

Matrix1 mmul2(Matrix1 const A, Matrix1 const B) {
   if (A.cols != B.rows) {
      fprintf(stderr, "Invalid dimensions");
      exit(1);
   }
   Matrix1 C = __M1_new(A.rows, B.cols);
   for (int row = 0; row < A.rows; row++)
      for (int col = 0; col < B.cols; col++)
         for (int idx = 0; idx < A.cols; idx++)
            C.data[row][col] += A.data[row][idx] * B.data[idx][col];
   return C;
}

int main() {
   // Define matrix dimensions
   const size_t rows = 1000;
   const size_t cols = 1000;
   
   // Initialize matrices
   Matrix1 A = __M1_new(rows, cols);
   Matrix1 B = __M1_new(cols, rows); // Making B square for simplicity

   // Fill matrices with random values
   srand(time(NULL));
   for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
         A.data[i][j] = (double)rand() / RAND_MAX;
         B.data[i][j] = (double)rand() / RAND_MAX;
      }
   }

   // Benchmark mmul1
   clock_t start = clock();
   Matrix1 result1 = mmul1(A, B);
   clock_t end = clock();
   double time_taken1 = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Time taken by mmul1: %f seconds\n", time_taken1);
   __M1_free(&result1);

   // Benchmark mmul2
   start = clock();
   Matrix1 result2 = mmul2(A, B);
   end = clock();
   double time_taken2 = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Time taken by mmul2: %f seconds\n", time_taken2);
   __M1_free(&result2);
   
   __M1_free(&A);
   __M1_free(&B);
   
   return 0;
}