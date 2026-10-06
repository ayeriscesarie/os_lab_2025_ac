CC = gcc
CFLAGS = -Wall -Wextra
PTHREAD = -pthread

all: mutex parallel_factorial deadlock

mutex: src/mutex.c
	$(CC) $(CFLAGS) $(PTHREAD) src/mutex.c -o mutex

parallel_factorial: src/parallel_factorial.c
	$(CC) $(CFLAGS) $(PTHREAD) src/parallel_factorial.c -o parallel_factorial

deadlock: src/deadlock.c
	$(CC) $(CFLAGS) $(PTHREAD) src/deadlock.c -o deadlock

clean:
	rm -f mutex parallel_factorial deadlock