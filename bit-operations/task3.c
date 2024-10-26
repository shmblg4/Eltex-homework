// Задание 3, найти количество единиц в целом положительном числе

#include <stdio.h>

// Функция счета единиц в числе
int find_ones(int x)
{
    int count = 0;
    for (int i = sizeof(int) * 8; i >= 0; i--)
        if ((1 << i) & x)
            count++;
    return count;
}

int main()
{
    int x; // Задаем число
    printf("Введите целое положительное число X = ");
    scanf("%d", &x);
    if (x < 0) // Ошибка если число не соответствует условию (положительное)
    {
        printf("\e[31mЧисло должно быть положительным\e[m\n");
        return 1;
    }
    printf("Число единиц в %d = %d\n", x, find_ones(x)); // Считаем единицы
    return 0;
}