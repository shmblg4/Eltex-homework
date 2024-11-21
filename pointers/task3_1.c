/* Напишите программу, которая заполняет двумерный массив размера MxN случайными числами. Используя только указатели,
вычислите сумму элементов каждой строки и каждого столбца без использования индексной нотации (т.е., без использования arr[i][j]).*/

#include <stdio.h>
#include <stdlib.h>

void fillRand(int *matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            *(matrix + i * n + j) = rand() % 100; // Ограничил для красоты :)
}

void printMatrix(int *matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", *(matrix + i * n + j));
        printf("\n");
    }
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int matrix[m][n];
    fillRand(&matrix[0][0], m, n);
    printMatrix(&matrix[0][0], m, n);
    return 0;
}