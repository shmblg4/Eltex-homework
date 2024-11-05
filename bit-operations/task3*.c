/* 3. Сжатие и распаковка данных:
Создайте программу, которая сжимает массив из восьми 8-битных значений
в одно 64-битное беззнаковое целое число с использованием битовых операций.
Реализуйте обратную функцию для восстановления исходного массива из сжатого значения. */

#include <stdio.h>

typedef long long uint64;

void print_Int64binary(uint64 x)
{
    for (int i = 63; i >= 0; i--)
    {
        printf("%llu", (x >> i) & 1);
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

void print_CharArraybinary(char *x, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = sizeof(char) * 8 - 1; j >= 0; j--)
        {
            if (*(x + i) & (1 << j))
                printf("1");
            else
                printf("0");
            if (j % 8 == 0)
                printf(" ");
        }
    }
    printf("\n");
}

uint64 toInt64(char *array)
{
    uint64 result = 0;
    int index = 64;
    for (int i = 0; i < 8; i++)
    {
        index -= 8;
        result |= (uint64)array[i] << index;
    }
    return result;
}

void fromInt64ToCharArr(char *result, uint64 target)
{
    int index = 64;
    for (int i = 0; i < 8; i++)
    {
        index -= 8;
        result[i] = (char)((~((uint64)(0xFF) << index) | target) >> index);
    }
}

int main()
{
    char arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint64 intfromArray = toInt64(&arr[0]);
    char new_arr[8];
    fromInt64ToCharArr(&new_arr[0], intfromArray);
    printf("Array char[8]:\t\t");
    print_CharArraybinary(&arr[0], 8);
    printf("Int64:\t\t\t");
    print_Int64binary(intfromArray);
    printf("New_array char[8]:\t");
    print_CharArraybinary(&new_arr[0], 8);

    return 0;
}