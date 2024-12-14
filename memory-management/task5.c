#include <stdio.h>
#include <stdlib.h>

// Функция вычисления факториала числа n рекурсией
int task(int n)
{
    if (n == 0)
        return 1;
    return n * task(n - 1);
}

int main()
{
    int n;
    printf("Введите n: ");
    scanf("%d", &n);
    int res = task(n);
    printf("Факториал числа %d равен %d\n", n, res);
    return 0;
}