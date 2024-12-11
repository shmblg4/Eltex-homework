#include <stdio.h>
#include <string.h>

#define MAX_ELEMS 100

typedef struct abonent
{
    char name[20]; // Увеличен размер с 10 на 20 для кириллицы
    char second_name[20];
    char tel[15];
} Abonent;

void init_Abonents(Abonent *array)
{
    memset(array, 0, sizeof(Abonent) * MAX_ELEMS);
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
    printf("Введите имя, фамилию и номер телефона\n");
    printf("Пример: Иван Иванов 1234567890\n");
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        if (is_empty(array + index))
        {
            scanf("%s", array[index].name);
            scanf("%s", array[index].second_name);
            scanf("%s", array[index].tel);
            printf("Add {%s %s %s} on %d pos.\n", array[index].name, array[index].second_name, array[index].tel, index);
            return;
        }
    }
}

int deluser(Abonent *array)
{
    int index;
    scanf("%d", &index);
    if (index < 0 || index >= MAX_ELEMS)
    {
        printf("Введите верный номер записи от 0 до %d\n", MAX_ELEMS - 1);
        return 1;
    }
    memset(&array[index], 0, sizeof(Abonent));
    return 0;
}

void findbyname(Abonent *array)
{
    char name[50] = {0};
    scanf("%s", name);
    printf("Найденные записи:\n");
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        if (strcmp(array[index].name, name) == 0)
        {
            print_struct(&array[index], index);
        }
    }
}

void printall(Abonent *array)
{
    for (int index = 0; index < MAX_ELEMS; index++)
    {
        if (!is_empty(&array[index]))
            print_struct(&array[index], index);
    }
}

int work_with_data(Abonent *array)
{
    int input;
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
    default:
        printf("Неверный ввод. Пожалуйста, попробуйте снова.\n");
        return 0;
    }
    return 0;
}

int main()
{
    Abonent array[MAX_ELEMS];
    init_Abonents(array);
    while (!work_with_data(array))
        ;
    return 0;
}