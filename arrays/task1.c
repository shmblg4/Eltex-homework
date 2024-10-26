// 1. Вывести квадратную матрицу по заданному N.
#include <stdio.h>

void print_square_matrix(int *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", *(matrix + n * i + j));
        printf("\n");
    }
}

int main()
{
    int N;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &N);
    int matrix[N][N];
    int val = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = val;
            val++;
        }
    }
    print_square_matrix(&matrix[0][0], N);
    return 0;
}