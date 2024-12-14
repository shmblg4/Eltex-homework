#include <stdio.h>
#include <stdlib.h>

typedef struct my_struct {
    int a;
    char b[10];
} my_struct;

void print_struct(my_struct *ptr) {
    printf("a: %d\n", ptr->a);
    printf("b: %s\n", ptr->b);
}

void task() {
    my_struct *ptr = (my_struct*)calloc(5, sizeof(my_struct));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        ptr[i].a = i + 1;
        scanf("%s", ptr[i].b);
        print_struct(&ptr[i]);
    }

    free(ptr);
}

int main() {
    task();
    return 0;
}