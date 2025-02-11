#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 10
#define MESSAGE_SIZE 256

typedef struct
{
    char messages[BUFFER_SIZE][MESSAGE_SIZE];
    int write_index;
    int read_index;
} SharedBuffer;

void sem_wait(int sem_id, int sem_num);
void sem_signal(int sem_id, int sem_num);

#endif