#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int server_socket;
int client_socket = -1;

void handle_sigio(int sig)
{
    char buffer[BUFFER_SIZE];

    if (client_socket < 0)
    {
        return;
    }

    ssize_t bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_read < 0)
    {
        perror("recv");
        return;
    }
    else if (bytes_read == 0)
    {
        printf("Client disconnected.\n");
        close(client_socket);
        client_socket = -1;
        return;
    }

    buffer[bytes_read] = '\0';
    printf("Received: %s\n", buffer);
}

int main()
{
    struct sockaddr_in server_addr, client_addr;
    struct sigaction sa;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Установка сокета в неблокирующий режим
    int flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK | O_ASYNC);

    // Установка владельца сокета для получения сигналов
    fcntl(server_socket, __F_SETOWN, getpid());

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigio;
    sigaction(SIGIO, &sa, NULL);

    printf("Server is listening on port %d...\n", PORT);

    // Основной цикл сервера
    while (1)
    {
        if (client_socket < 0)
        {
            client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
            if (client_socket < 0)
            {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    continue;
                }
                else
                {
                    perror("accept");
                    break;
                }
            }

            // Установка клиентского сокета в неблокирующий режим
            flags = fcntl(client_socket, F_GETFL, 0);
            fcntl(client_socket, F_SETFL, flags | O_NONBLOCK | O_ASYNC);

            // Установка владельца сокета для получения сигналов
            fcntl(client_socket, __F_SETOWN, getpid());

            printf("Client connected.\n");
        }

        pause(); // Ожидание сигнала
    }

    // Закрытие сокетов
    if (client_socket >= 0)
    {
        close(client_socket);
    }
    close(server_socket);
    return 0;
}
