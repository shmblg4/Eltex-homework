#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define THREAD_COUNT 4

int array[ARRAY_SIZE];                // Массив для вычислений
int partial_sums[THREAD_COUNT] = {0}; // Массив для хранения частичных сумм

// Функция, которую выполняет каждый поток
void *calculate_partial_sum(void *arg)
{
    int thread_id = *(int *)arg;                         // Получаем ID потока
    int start = thread_id * (ARRAY_SIZE / THREAD_COUNT); // Начало диапазона
    int end = start + (ARRAY_SIZE / THREAD_COUNT);       // Конец диапазона

    // Вычисляем сумму квадратов для своей части массива
    for (int i = start; i < end; i++)
    {
        partial_sums[thread_id] += array[i] * array[i];
    }

    pthread_exit(NULL); // Завершаем поток
}

int main()
{
    pthread_t threads[THREAD_COUNT]; // Массив идентификаторов потоков
    int thread_ids[THREAD_COUNT];    // Массив ID потоков

    // Инициализируем массив случайными значениями
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i + 1;
    }

    // Создаём потоки
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread_ids[i] = i; // Присваиваем ID потоку
        pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_ids[i]);
    }

    // Ожидаем завершения всех потоков
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Суммируем частичные суммы
    int total_sum = 0;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        total_sum += partial_sums[i];
    }

    printf("Total sum: %d\n", total_sum);

    return 0;
}