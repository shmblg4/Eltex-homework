/*valgrind --leak-check=yes ./app
==26641== Memcheck, a memory error detector
==26641== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==26641== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==26641== Command: ./app
==26641==
1 2 3 4 5 ==26641==
==26641== HEAP SUMMARY:
==26641==     in use at exit: 20 bytes in 1 blocks
==26641==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==26641==
==26641== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
==26641==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==26641==    by 0x10919E: task() (in /home/shmblg4/sibguti/Eltex-Embedded-C/memory-management/app)
==26641==    by 0x109237: main (in /home/shmblg4/sibguti/Eltex-Embedded-C/memory-management/app)
==26641==
==26641== LEAK SUMMARY:
==26641==    definitely lost: 20 bytes in 1 blocks
==26641==    indirectly lost: 0 bytes in 0 blocks
==26641==      possibly lost: 0 bytes in 0 blocks
==26641==    still reachable: 0 bytes in 0 blocks
==26641==         suppressed: 0 bytes in 0 blocks
==26641==
==26641== For lists of detected and suppressed errors, rerun with: -s
==26641== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)*/

#include <stdio.h>
#include <stdlib.h>

void task()
{
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < 5; i++)
        arr[i] = i + 1;
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    // Oops! Memory leak!
    // free(arr);
}

int main()
{
    task();
    return 0;
}