#include "shared-memory.h"

// Ожидание семафора
void sem_wait(int sem_id, int sem_num)
{
    struct sembuf op = {sem_num, -1, 0};
    semop(sem_id, &op, 1);
}

// Сигнал семафора
void sem_signal(int sem_id, int sem_num)
{
    struct sembuf op = {sem_num, 1, 0};
    semop(sem_id, &op, 1);
}

int main()
{
    key_t key = ftok("shmfile", 65);
    int shm_id = shmget(key, sizeof(SharedBuffer), 0666 | IPC_CREAT);
    SharedBuffer *buffer = (SharedBuffer *)shmat(shm_id, NULL, 0);

    int sem_id = semget(key, 3, 0666 | IPC_CREAT);
    semctl(sem_id, 0, SETVAL, 1);
    semctl(sem_id, 1, SETVAL, BUFFER_SIZE);
    semctl(sem_id, 2, SETVAL, 0);

    pid_t producer_pid = fork();
    if (producer_pid == 0)
    {
        for (int i = 0; i < 20; i++)
        {
            char message[MESSAGE_SIZE];
            snprintf(message, MESSAGE_SIZE, "Message %d", i);

            sem_wait(sem_id, 1);
            sem_wait(sem_id, 0);

            strcpy(buffer->messages[buffer->write_index], message);
            buffer->write_index = (buffer->write_index + 1) % BUFFER_SIZE;

            sem_signal(sem_id, 0);
            sem_signal(sem_id, 2);

            printf("Producer: %s\n", message);
            sleep(1);
        }
        exit(0);
    }

    for (int i = 0; i < 2; i++)
    {
        pid_t consumer_pid = fork();
        if (consumer_pid == 0)
        {
            while (1)
            {
                sem_wait(sem_id, 2);
                sem_wait(sem_id, 0);

                char message[MESSAGE_SIZE];
                strcpy(message, buffer->messages[buffer->read_index]);
                buffer->read_index = (buffer->read_index + 1) % BUFFER_SIZE;

                sem_signal(sem_id, 0);
                sem_signal(sem_id, 1);

                printf("Consumer %d: %s\n", i + 1, message);
                sleep(2);
            }
            exit(0);
        }
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    shmdt(buffer);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);

    return 0;
}