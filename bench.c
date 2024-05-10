#include "includes/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for sleep

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

Matrix1 mmul_blocked(Matrix1 const A, Matrix1 const B) {
   if (A.cols != B.rows) {
      fprintf(stderr, "Invalid dimensions");
      exit(1);
   }
   Matrix1 C = __M1_new(A.rows, B.cols);
   const int BLOCK_SIZE = 4;
   for (int row = 0; row < A.rows; row++)
      for (int block = 0; block < A.cols; block += BLOCK_SIZE)
         for (int chunk = 0; chunk < A.cols; chunk += BLOCK_SIZE)
            for (int sub_chunk = 0; sub_chunk < BLOCK_SIZE; sub_chunk++)
               for (int idx = 0; idx < BLOCK_SIZE; idx++)
                  C.data[row][block + idx] += A.data[row][chunk + sub_chunk] * B.data[chunk + sub_chunk][block + idx];
   return C;
}

int main() {
   // Define matrix dimensions
   const size_t rows = 1000;
   const size_t cols = 101;

   // Initialize matrices
   Matrix1 A = __M1_new(rows, cols);
   Matrix1 B = __M1_new(cols, rows); // Making B square for simplicity

   // Fill matrices with random values
   srand(time(NULL));
   for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
         A.data[i][j] = (double)rand() / RAND_MAX;
         B.data[j][i] = (double)rand() / RAND_MAX;
      }
   }

   //   // Benchmark mmul1
   //   clock_t start = clock();
   //   Matrix1 result1 = mmul1(A, B);
   //   clock_t end = clock();
   //   double time_taken1 = ((double)(end - start)) / CLOCKS_PER_SEC;
   //   printf("Time taken by mmul1: %f seconds\n", time_taken1);
   //   __M1_free(&result1);
   //
   //   sleep(5);

   // Benchmark mmul2
   clock_t start = clock();
   Matrix1 result2 = mmul2(A, B);
   clock_t end = clock();
   double time_taken2 = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Time taken by mmul2: %f seconds\n", time_taken2);
   __M1_free(&result2);

   sleep(5);

   start = clock();
   Matrix1 result3 = mmul_blocked(A, B);
   end = clock();
   double time_taken3 = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Time taken by mmul_blocked: %f seconds\n", time_taken3);
   __M1_free(&result3);

   sleep(5);

   __M1_free(&A);
   __M1_free(&B);

   return 0;
}