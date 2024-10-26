// 3. Заполнить верхний треугольник матрицы 1, а нижний 0.

#include <stdio.h>

// Функция вывода матрицы
void print_square_matrix(int *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", *(matrix + n * i + j));
        printf("\n");
    }
}

// Заполнение матрицы с единичным главным треугольником
void fill_matrix(int *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < i)
            {
                *(matrix + n * i + j) = 0; // Заполнение нижнего треугольника нулями
            }
            else
            {
                *(matrix + n * i + j) = 1; // Заполнение верхнего треугольника единицами
            }
        }
    }
}

int main()
{
    int N;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &N);
    int matrix[N][N];

    fill_matrix(&matrix[0][0], N);
    print_square_matrix(&matrix[0][0], N);
    return 0;
}