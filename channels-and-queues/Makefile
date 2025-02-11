all: fifo sysv posix

fifo: fifo-example.c
	gcc fifo-example.c -o fifo

sysv: sysv-example.c
	gcc sysv-example.c -o sysv

posix: posix-example.c
	gcc posix-example.c -o posix

compare: fifo sysv posix
	./fifo
	./sysv
	./posix

.PHONY: clean
clean:
	rm -f fifo sysv posix