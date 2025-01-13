# Задача 1: Создание статической библиотеки
task1: comp lib app

comp: calc.c io.c helper.c
	gcc -c $^

lib: calc.o io.o helper.o
	ar rcs libapp.a $^

app: task1-2.c
	gcc -o app task1-2.c -L. -lapp

# Задача 2: Создание динамической библиотеки
task2: comp2 lib2 app2

comp2: calc.c io.c helper.c
	gcc -c -fPIC $^

lib2: calc.o io.o helper.o
	gcc -shared $^ -o libapp.so

app2: task1-2.c
	gcc task1-2.c -L. -lapp -Wl,-rpath,. -o app2

# Задача 3: Динамическая загрузка библиотеки
task3: app3

app3: task3.c
	gcc task3.c -ldl -o app3

# Пустое правило для task3, чтобы отключить неявное правило
task3: ;

# Очистка
clean:
	rm -f *.o *.a *.so app app2 app3