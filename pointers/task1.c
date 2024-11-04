#include <stdio.h>

void print_binary(int x)
{
    for (int i = sizeof(x) * 8 - 1; i >= 0; i--)
    {
        if (x & (1 << i))
            printf("1");
        else
            printf("0");

        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int x;
    printf("Введите целое положительное число X = ");
    scanf("%d", &x);
    if (x < 0)
    {
        printf("\e[31mЧисло должно быть положительным\e[m\n");
        return 1;
    }

    unsigned char y;
    printf("Введите целое положительное число Y меньше чем 256, Y = ");
    scanf("%hhu", &y); // Используем %hhu для scanf для unsigned char
    if (y < 0 || y >= 256)
    {
        printf("\e[31mНеверное число, Y должно быть положительным и меньше 256\e[m\n");
        return 1;
    }

    printf("Исходное значение X в двоичном формате:\n");
    print_binary(x); // Вывод начального значения

    unsigned char *ptr = (unsigned char *)&x; // Приводим к указателю на байт
    ptr[2] = y;                               // Устанавливаем значение третьего байта

    printf("Значение X после изменения третьего байта:\n");
    print_binary(x); // Вывод измененного значения

    return 0;
}
