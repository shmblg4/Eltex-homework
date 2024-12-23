#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "\e[31mError!\e[m\nUsage: %s <file> <line>\n", argv[0]);
        return 1;
    }

    // Откроем файл для записи (добавления строки)
    int fd_write = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_write < 0)
    {
        fprintf(stderr, "\e[31mError!\e[m Failed to open file for writing\n");
        return 1;
    }

    // Запишем в файл строку
    size_t bytes_written = write(fd_write, argv[2], strlen(argv[2]));
    if (bytes_written < 0)
    {
        fprintf(stderr, "\e[31mError!\e[m Failed to write to file\n");
        close(fd_write);
        return 1;
    }

    // Добавим новую строку для читаьельности результата
    write(fd_write, "\n", 1);

    close(fd_write);

    // Откроем файл для чтения
    int fd_read = open(argv[1], O_RDONLY);
    if (fd_read < 0)
    {
        fprintf(stderr, "\e[31mError!\e[m Failed to open file for reading\n");
        return 1;
    }

    // Читаем строку
    char buffer[1024];
    size_t bytes_read = read(fd_read, buffer, sizeof(buffer) - 1); // Не читаем символ конца строки
    if (bytes_read < 0)
    {
        fprintf(stderr, "\e[31mError!\e[m Failed to read from file\n");
        close(fd_read);
        return 1;
    }

    buffer[bytes_read] = '\0'; // Добавляем символ конца строки
    printf("%s", buffer);

    close(fd_read);
    return 0;
}
