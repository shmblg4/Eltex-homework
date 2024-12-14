#include <stdio.h>
#include <stdlib.h>

void task()
{
    char** arr = (char **)malloc(3 * sizeof(char *));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    printf("\e[33mBefore reallocation:\e[m\n");
    arr[0] = "first";
    arr[1] = "second";
    arr[2] = "third";
    for (int i = 0; i < 3; i++)
        printf("%s\n", arr[i]);
    
    arr = (char **)realloc(arr, 5 * sizeof(char *));
    arr[3] = "fourth";
    arr[4] = "fifth";
    printf("\e[33mAfter reallocation:\e[m\n");
    for (int i = 0; i < 5; i++)
        printf("%s\n", arr[i]);
    free(arr);
}

int main()
{
    task();
    return 0;
}