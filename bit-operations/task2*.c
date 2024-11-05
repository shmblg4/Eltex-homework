// 2. Манипуляция отдельными битами:
// Реализуйте функции для установки, сброса
// и инвертирования заданного бита в беззнаковом 32-битном числе.
// Напишите программу, которая демонстрирует работу этих функций на различных примерах.

#include <stdio.h>

void print_binary(unsigned int x)
{
    for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--)
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

void set_bit(unsigned int *x, short int n)
{
    if (n > 32 && n < 0)
        return;
    else
        *x |= (1 << n); // Устанавливаем заданный бит 0 -> 1; 1 -> 1
}

void invert_bit(unsigned int *x, short int n)
{
    if (n > 32 && n < 0)
        return;
    else
        *x ^= (1 << n); // Инвертируем бит 0 -> 1; 1 -> 0
}

void reset_bit(unsigned int *x, short int n)
{
    if (n > 32 && n < 0)
        return;
    else
        *x &= ~(1 << n); // Сбрасываем бит 0 -> 0; 1 -> 0
}

int main()
{
    unsigned int x; // Задаем число
    printf("Введите целое беззнаковое число X = ");
    scanf("%d", &x);
    print_binary(x);

    printf("Установим 9 и 11 биты\n");
    set_bit(&x, 9);
    set_bit(&x, 11);
    print_binary(x);

    printf("Сбросим 9 бит\n");
    reset_bit(&x, 9);
    print_binary(x);

    printf("Инвертируем 9 и 11 биты\n");
    invert_bit(&x, 9);
    invert_bit(&x, 11);
    print_binary(x);
    return 0;
}