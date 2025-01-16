#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child()
{
    // Массив аргументов для команды ls -l
    char *argv1[] = {"ls", "-l", NULL};

    // Выполняем команду
    int err = execvp("ls", argv1);
    if (err < 0) // Если произошла ошибка
    {
        perror("Error while executing command"); // Выводим сообщение
        exit(1);                                 // Завершаем программу
    }
}

int main()
{
    // Создаём дочерний процесс
    int pid = fork();

    if (pid < 0) // Если произошла ошибка
    {
        perror("Error while forking");
        return 1;
    }

    if (pid == 0) // Если это дочерний процесс
    {
        child(); // Выполняем команду
    }
    else
    {
        // Родительский процесс ждёт завершения дочернего
        waitpid(pid, NULL, 0);
        printf("Parent process ended\n"); // Выводим сообщение
    }

    return 0;
}