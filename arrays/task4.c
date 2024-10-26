// 3. Заполнить верхний треугольник матрицы 1, а нижний 0.

#include <stdio.h>

// Функция вывода матрицы
void print_square_matrix(int *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", *(matrix + n * i + j));
        printf("\n");
    }
}

// Заполнение матрицы улиткой
void snail_fill_matrix(int *matrix, int n) {
    int direction = 0; // 0 - вправо, 1 - вниз, 2 - влево, 3 - вверх
    int col, row;
    int left_col = 0, right_col = n - 1;
    int upper_row = 0, bottom_row = n - 1;
    int val = 1;

    while (val <= n * n) {
        switch (direction) {
            case 0: // Вправо
                for (col = left_col; col <= right_col; col++) {
                    *(matrix + n * upper_row + col) = val++;
                }
                upper_row++;
                break;

            case 1: // Вниз
                for (row = upper_row; row <= bottom_row; row++) {
                    *(matrix + n * row + right_col) = val++;
                }
                right_col--;
                break;

            case 2: // Влево
                for (col = right_col; col >= left_col; col--) {
                    *(matrix + n * bottom_row + col) = val++;
                }
                bottom_row--;
                break;

            case 3: // Вверх
                for (row = bottom_row; row >= upper_row; row--) {
                    *(matrix + n * row + left_col) = val++;
                }
                left_col++;
                break;
        }
        // Изменяем направление
        direction = (direction + 1) % 4;
    }
}

int main()
{
    int N;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &N);
    int matrix[N][N];

    snail_fill_matrix(&matrix[0][0], N);
    print_square_matrix(&matrix[0][0], N);
    return 0;
}