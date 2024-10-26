// 2. Вывести заданный массив размером N в обратном порядке.

#include <stdio.h>

void print_array_reversed(int *arr, int n)
{
    for (int i = n-1; i >= 0; i--)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main()
{
    int N;
    printf("Введите размер массива N: ");
    scanf("%d", &N);
    int arr[N];
    printf("Введите массив длинной N: ");
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    print_array_reversed(&arr[0], N);
    return 0;
}