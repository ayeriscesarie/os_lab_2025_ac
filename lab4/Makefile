CC = gcc
CFLAGS = -Wall -Wextra
PTHREAD = -pthread

all: parallel_min_max_lab4 process_memory parallel_sum

parallel_min_max_lab4: ../lab3/src/parallel_min_max_lab4.c ../lab3/src/find_min_max.c ../lab3/src/utils.c
	$(CC) $(CFLAGS) ../lab3/src/parallel_min_max_lab4.c ../lab3/src/find_min_max.c ../lab3/src/utils.c -o parallel_min_max_lab4

process_memory: src/process_memory.c
	$(CC) $(CFLAGS) src/process_memory.c -o process_memory

parallel_sum: src/parallel_sum.c src/sum.c ../lab3/src/utils.c
	$(CC) $(CFLAGS) $(PTHREAD) src/parallel_sum.c src/sum.c ../lab3/src/utils.c -I../lab3/src -o parallel_sum

clean:
	rm -f parallel_min_max_lab4 process_memory parallel_sum