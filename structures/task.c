#include <stdio.h>
#include <string.h>

#define MAX_ELEMS 100

typedef struct abonent
{
    char name[10];
    char second_name[10];
    char tel[10];
} Abonent;

void init_Abonents(Abonent *array)
{
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        *(array + index)->name = 0;
        *(array + index)->second_name = 0;
        *(array + index)->tel = 0;
    }
}

void print_struct(Abonent *elem, int index)
{
    printf("n: %d\n", index + 1);
    printf("%s\n", elem->name);
    printf("%s\n", elem->second_name);
    printf("%s\n\n", elem->tel);
}

int is_empty(Abonent *elem)
{
    return (strlen(elem->name) == 0) || (strlen(elem->second_name) == 0) || (strlen(elem->tel) == 0);
}

void adduser(Abonent *array)
{
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        if (is_empty(array + index))
        {
            scanf("%s", (array + index)->name);
            scanf("%s", (array + index)->second_name);
            scanf("%s", (array + index)->tel);
            printf("Add {%s %s %s} on %d pos.\n", (array + index)->name, (array + index)->second_name, (array + index)->tel, index);
            return;
        }
    }
}

int deluser(Abonent *array)
{
    int index;
    scanf("%d", &index);
    if (index < 0 || index > 99)
    {
        printf("Введите верный номер записи от 0 до 99\n");
        return 1;
    }
    *(array + index)->name = 0;
    *(array + index)->second_name = 0;
    *(array + index)->tel = 0;
    return 0;
}

void findbyname(Abonent *array)
{
    char name[50] = {0};
    scanf("%s", &name[0]);
    printf("Найденные записи:\n");
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        if (!strcmp((array + index)->name, name))
            print_struct((array + index), index);
        else
            continue;
    }
}

void printall(Abonent *array)
{
    int index = 0;
    while (index < 100)
    {
        if (!is_empty(array + index))
            print_struct((array + index), index);
        index++;
    }
}

int work_with_data(Abonent *array)
{
    int input = 5;
    printf("1) Добавить абонента\n"
           "2) Удалить абонента\n"
           "3) Поиск абонентов по имени\n"
           "4) Вывод всех записей\n"
           "5) Выход\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        adduser(array);
        break;
    case 2:
        deluser(array);
        break;
    case 3:
        findbyname(array);
        break;
    case 4:
        printall(array);
        break;
    case 5:
        return 1;
        break;

    default:
        return 1;
        break;
    }
    return 0;
}

int main()
{
    Abonent array[MAX_ELEMS];
    init_Abonents(&array[0]);
    while (!work_with_data(&array[0]));
    return 0;
}