// Задание 2, вывести двоичное представление отрицательного числа

#include <stdio.h>

// Функция вывода бинарного числа
void print_binary(int x)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) // Полностью выводим число
        if (x & (1 << i))
            printf("1");
        else
            printf("0");
    printf("\n");
}

int main()
{
    int x; // Задаем число
    printf("Введите целое отрицательное число X = ");
    scanf("%d", &x);
    if (x >= 0) // Ошибка если число не соответствует условию (отрицательное)
    {
        printf("\e[31mЧисло должно быть отрицательным\e[m\n");
        return 1;
    }
    print_binary(x); // Выводим число
    return 0;
}