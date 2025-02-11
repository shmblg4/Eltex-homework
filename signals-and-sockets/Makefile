all: server client

server: async-server.c
	gcc -o server async-server.c

client: async-client.c
	gcc -o client async-client.c

run-server:
	./server

run-client:
	./client

.PHONY: all server client run-server run-client

clean:
	rm -f server client