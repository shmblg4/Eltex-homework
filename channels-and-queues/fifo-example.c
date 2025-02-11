#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/time.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_NAME "my_fifo"
#define NUM_MESSAGES 1000
#define MESSAGE "Hello, FIFO!"

int main()
{
    pid_t pid;
    int fd;
    struct timespec start, end;
    char buffer[sizeof(MESSAGE)];

    // Создаем FIFO, если оно не существует
    mkfifo(FIFO_NAME, 0666);

    // Замеряем время начала
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Создаем дочерний процесс
    pid = fork();

    if (pid == 0)
    { // Дочерний процесс (receiver)
        fd = open(FIFO_NAME, O_RDONLY);
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            read(fd, buffer, sizeof(buffer));
        }
        close(fd);
        return 0;
    }
    else if (pid > 0)
    { // Родительский процесс (sender)
        fd = open(FIFO_NAME, O_WRONLY);
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            write(fd, MESSAGE, sizeof(MESSAGE));
        }
        close(fd);

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Замеряем время окончания
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Вычисляем общее время передачи
        float time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
        printf("FIFO: Total time = %f s\n", time_spent * 1e-9);

        // Удаляем FIFO
        unlink(FIFO_NAME);
    }
    else
    {
        perror("fork");
        return 1;
    }

    return 0;
}