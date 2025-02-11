#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define MESSAGE "Hello, server!"

int main()
{
    int client_socket;
    struct sockaddr_in server_addr;

    // Создание сокета
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Подключение к серверу
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения на сервер
    if (send(client_socket, MESSAGE, strlen(MESSAGE), 0) < 0)
    {
        perror("send");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", MESSAGE);

    // Закрытие сокета
    close(client_socket);
    return 0;
}