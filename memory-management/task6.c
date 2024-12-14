#include <stdio.h>
#include <stdlib.h>

void task() {
    char *static_arr[2] = {NULL, NULL};
    char **dynamic_arr = (char **)malloc(2 * sizeof(char *));
    if (dynamic_arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    dynamic_arr[0] = "first";
    dynamic_arr[1] = "second";
    static_arr[0] = dynamic_arr[0];
    static_arr[1] = dynamic_arr[1];
    printf("\e[33mStatic array:\e[m\n");
    for (int i = 0; i < 2; i++)
        printf("%s\n", static_arr[i]);

    printf("\e[33mDynamic array:\e[m\n");
    for (int i = 0; i < 2; i++)
        printf("%s\n", dynamic_arr[i]);
    free(dynamic_arr);
}

int main() {
    task();
    return 0;
}