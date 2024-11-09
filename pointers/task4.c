// Напишите программу, которая ищет в введенной строке (с клавиатуры)
// введенную подстроку (с клавиатуры) и возвращает указатель на начало
// подстроки, если подстрока не найдена в указатель записывается NULL.
// В качестве срок использовать статические массивы

#include <stdio.h>
#include <string.h>

char *find_in_str(char *ptr_str, char *ptr_sub)
{
    while (*ptr_str != '\0')
    {
        char *sub_start = ptr_sub;

        if (*ptr_str == *sub_start)
        {
            char *start = ptr_str;
            while (*sub_start != '\0' && *ptr_str != '\0' && *ptr_str == *sub_start)
            {
                ptr_str++;
                sub_start++;
            }

            if (*sub_start == '\0')
            {
                return start;
            }

            ptr_str = start;
        }

        ptr_str++;
    }
    return NULL;
}

int main()
{
    char str[100];
    printf("Введите строку: ");
    fgets(str, 100, stdin);

    str[strcspn(str, "\n")] = '\0';

    char sub_str[100];
    printf("Введите подстроку: ");
    fgets(sub_str, 100, stdin);

    sub_str[strcspn(sub_str, "\n")] = '\0';

    char *ptr = find_in_str(str, sub_str);

    if (ptr != NULL)
    {
        printf("Подстрока найдена: %s, адрес: %p\n", ptr, (void *)ptr);
    }
    else
    {
        printf("Подстрока не найдена.\n");
    }

    return 0;
}
