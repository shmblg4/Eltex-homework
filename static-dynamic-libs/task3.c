#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // Для dlopen, dlsym, dlclose

int main()
{
    void *handle;
    char *error;

    // Открываем динамическую библиотеку
    handle = dlopen("./libapp.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    // Получаем адрес функции add
    int (*fact)(int) = dlsym(handle, "fact");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "Ошибка получения адреса функции: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Получаем адрес функции print_result
    void (*print_result)(int) = dlsym(handle, "print_result");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "Ошибка получения адреса функции: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Используем функции из библиотеки
    int a = 5;
    int result = fact(a);
    print_result(result);

    // Закрываем библиотеку
    dlclose(handle);

    return 0;
}