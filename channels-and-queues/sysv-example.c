#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <linux/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG_KEY 1234
#define NUM_MESSAGES 1000
#define MESSAGE "Hello, SysV!"

struct msgbuf
{
    long mtype;
    char mtext[sizeof(MESSAGE)];
};

int main()
{
    pid_t pid;
    int msqid;
    struct msgbuf msg;
    struct timespec start, end;

    // Создаем очередь сообщений
    msqid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msqid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Замеряем время начала
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Создаем дочерний процесс
    pid = fork();

    if (pid == 0)
    { // Дочерний процесс (receiver)
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0);
        }
        return 0;
    }
    else if (pid > 0)
    { // Родительский процесс (sender)
        msg.mtype = 1;
        strcpy(msg.mtext, MESSAGE);

        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
        }

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Замеряем время окончания
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Вычисляем общее время передачи
        float time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
        printf("System V: Total time = %f s\n", time_spent * 1e-9);

        // Удаляем очередь сообщений
        msgctl(msqid, IPC_RMID, NULL);
    }
    else
    {
        perror("fork");
        return 1;
    }

    return 0;
}