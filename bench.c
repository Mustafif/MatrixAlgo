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

   // Calculate padded sizes
   int padded_rows = (A.rows + 7) & (~7); // Round up to multiple of 8
   int padded_cols = (B.cols + 7) & (~7); // Round up to multiple of 8

   // Create padded matrices
   Matrix1 Apadded = __M1_new(padded_rows, A.cols);
   Matrix1 Bpadded = __M1_new(B.rows, padded_cols);
   Matrix1 Cpadded = __M1_new(padded_rows, padded_cols);

   // Copy data to padded matrices
   for (int i = 0; i < A.rows; i++)
      for (int j = 0; j < A.cols; j++)
         Apadded.data[i][j] = A.data[i][j];
   for (int i = 0; i < B.rows; i++)
      for (int j = 0; j < B.cols; j++)
         Bpadded.data[i][j] = B.data[i][j];

   // Perform matrix multiplication on padded matrices
   int rows_per_block = 8;
   int cols_per_block = 8;
   for (int row_block = 0; row_block < padded_rows; row_block += rows_per_block)
      for (int col_block = 0; col_block < padded_cols; col_block += cols_per_block)
         for (int row = row_block; row < row_block + rows_per_block; row++)
            for (int col = col_block; col < col_block + cols_per_block; col++)
               for (int idx = 0; idx < A.cols; idx++)
                  Cpadded.data[row][col] += Apadded.data[row][idx] * Bpadded.data[idx][col];

   // Copy result to output matrix
   Matrix1 C = __M1_new(A.rows, B.cols);
   for (int i = 0; i < A.rows; i++)
      for (int j = 0; j < B.cols; j++)
         C.data[i][j] = Cpadded.data[i][j];

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
   const size_t cols = 100;

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