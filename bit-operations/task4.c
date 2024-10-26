// Задание 4, поменять в числе третий байн на введенный с клавиатуры

#include <stdio.h>

// Функция вывода бинарного числа c отдельным выводом байтов для наглядности
void print_binary(int x)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) // Полностью выводим число
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

int change_third_byte(int x, int y)
{
    x = (x & 0xff00ffff) | (y << 16); // 0xff00ffff это маска, зануляем 3 байт
    return x;
}

int main()
{
    int x, y; // Задаем числа
    printf("Введите целое положительное число X = ");
    scanf("%d", &x);
    if (x < 0) // Ошибка если число не соответствует условию (положительное)
    {
        printf("\e[31mЧисло должно быть положительным\e[m\n");
        return 1;
    }
    printf("Введите положительное число меньше чем 256: ");
    scanf("%d", &y);
    if (y < 0 || y > 255) // Ошибка если число не соответствует условию (положительное и не больше 1 байта)
    {
        printf("\e[31mЧисло должно быть положительным и не более 1 байта\e[m\n");
        return 1;
    }
    x = change_third_byte(x, y);
    print_binary(x);
    return 0;
}