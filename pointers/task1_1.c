/* Напишите функцию на языке С, которая принимает строку
и переворачивает её в обратном порядке, используя только указатели.
Вы не должны использовать дополнительные массивы или стандартные функции библиотеки, такие как strrev. */

#include <stdio.h>
#define MAX_LENGHT 50

int getlenght(char *str)
{
    int len = 0;
    for (len; *(str + len) != '\n'; len++);
    return len;
}

// Решил что нужно не просто вывести в обратном порядке, а именно изменить саму строку
void reverseStr(char *str)
{
    int max = getlenght(str) - 1;
    int min = 0;
    while (max > min)
    {   
        char tmp = *(str + max);
        *(str + max) = *(str + min);
        *(str + min) = tmp;
        max--;
        min++;
    }
}

int main()
{
    char str[50];
    printf("Введите строку макс. длиной 50 символов\n");
    fgets(&str[0], MAX_LENGHT, stdin);
    reverseStr(&str[0]);
    printf("%s", str);
    return 0;
}