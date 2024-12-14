## Выводы о использовании стека и локальной памяти
```bash
==33743== Memcheck, a memory error detector
==33743== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==33743== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==33743== Command: ./app
==33743== 
Введите n: 5
Факториал числа 5 равен 120
==33743== 
==33743== HEAP SUMMARY:
==33743==     in use at exit: 0 bytes in 0 blocks
==33743==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==33743== 
==33743== All heap blocks were freed -- no leaks are possible
==33743== 
==33743== For lists of detected and suppressed errors, rerun with: -s
==33743== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
- Программа сделала 2 выделения памяти (allocs) и 2 освобождения (frees), что указывает на корректное использование кучи
- Объем выделенной динамической памяти составил 2048 байт.
- Все выделенные блоки памяти были освобождены ("All heap blocks were freed"), что исключает утечки памяти
- "ERROR SUMMARY: 0 errors from 0 contexts" говорит о том, что в программе нет ошибок использования памяти.