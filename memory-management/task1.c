#include <stdio.h>
#include <stdlib.h>

void task()
{
    printf("Введите размер массива: ");
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Введите элементы массива: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    free(arr);
}

int main()
{
    task();
    return 0;
}