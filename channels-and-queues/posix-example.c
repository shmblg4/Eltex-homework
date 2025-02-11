#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define QUEUE_NAME "/my_queue"
#define NUM_MESSAGES 1000
#define MESSAGE "Hello, POSIX!"

int main()
{
    pid_t pid;
    mqd_t mq;
    struct timespec start, end;
    char buffer[sizeof(MESSAGE)];

    // Создаем очередь сообщений
    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = sizeof(MESSAGE),
        .mq_curmsgs = 0};
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1)
    {
        perror("mq_open");
        return 1;
    }

    // Замеряем время начала
    clock_gettime(1, &start);

    // Создаем дочерний процесс
    pid = fork();

    if (pid == 0)
    { // Дочерний процесс (receiver)
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            mq_receive(mq, buffer, sizeof(buffer), NULL);
        }
        return 0;
    }
    else if (pid > 0)
    { // Родительский процесс (sender)
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            mq_send(mq, MESSAGE, sizeof(MESSAGE), 0);
        }

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Замеряем время окончания
        clock_gettime(1, &end);

        // Вычисляем общее время передачи
        float time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
        printf("POSIX: Total time = %f s\n", time_spent * 1e-9);

        // Закрываем и удаляем очередь
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    }
    else
    {
        perror("fork");
        return 1;
    }

    return 0;
}