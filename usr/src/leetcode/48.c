#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int matrixSize) {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_row(int *row, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", row[i]);
  }
  printf("\n");
}

void swap(int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void rotate(int **matrix, int matrixSize, int *matrixColSize) {
  int row[matrixSize];
  int row_len, i, count, row_start, rnd_shift;

  row_len = matrixSize - 1;
  row_start = 0;
  rnd_shift = 0;

  while (row_start < row_len) {
    count = 0;
    // copy first row to row
    for (i = row_start; i <= row_len; i++) {
      row[i] = matrix[row_start][i];
    }

    while (count < 4) {
      if (count == 0) {

        for (i = row_start; i <= row_len; i++) {
          swap(&matrix[i][row_len], &row[i]);
        }
      } else if (count == 1) {

        for (i = row_start; i <= row_len; i++) {
          swap(&matrix[row_len][i], &row[row_len - i + rnd_shift]);
        }
      } else if (count == 2) {

        for (i = row_start; i <= row_len - 1; i++) {
          swap(&matrix[i][row_start], &row[row_len - i + rnd_shift]);
        }
      } else if (count == 3) {
        for (i = row_start + 1; i <= row_len - 1; i++) {
          swap(&matrix[row_start][i], &row[i]);
        }
      }

      count++;
    }

    row_start++;
    row_len--;
    rnd_shift++;
  }
}

int main() {

  int matrixSize = 4, i, j;

  int **matrix = calloc(matrixSize, sizeof(int *));

  int data[] = {5, 1, 9, 11, 2, 4, 8, 10, 13, 3, 6, 7, 15, 14, 12, 16};

  for (i = 0; i < matrixSize; i++) {
    matrix[i] = calloc(matrixSize, sizeof(int));
    for (j = 0; j < matrixSize; j++) {
      matrix[i][j] = data[i * matrixSize + j];
    }
  }

  rotate(&matrix[0], matrixSize, NULL);

  return 0;
}
