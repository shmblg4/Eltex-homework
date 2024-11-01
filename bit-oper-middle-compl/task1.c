// 1. Подсчет битовых паритетов:
// Напишите функцию на языке С, которая определяет,
// имеет ли беззнаковое целое число четное или нечетное количество
// установленных битов (битовый паритет).
// Функция должна возвращать 1, если количество установленных битов четное,
// и 0, если нечетное, без использования встроенных функций.

#include <stdio.h>

void print_binary(int x)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        if (x & (1 << i))
            printf("1");
        else
            printf("0");
    printf("\n");
}

int bit_parity(int x)
{
    short int ones = 0;
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        if (x & (1 << i))
            ones++;
        else
            continue;
    return ones % 2 == 0;
}

int main()
{
    unsigned int x; // Задаем число
    printf("Введите целое положительное число X = ");
    scanf("%d", &x);
    if (x < 0) // Ошибка если число не соответствует условию (положительное)
    {
        printf("\e[31mЧисло должно быть положительным\e[m\n");
        return 1;
    }
    print_binary(x); // Выводим число
    switch (bit_parity(x))
    {
    case 1:
        printf("Число бит четное\n");
        break;

    default:
        printf("Число бит нечетное\n");
        break;
    }

    return 0;
}