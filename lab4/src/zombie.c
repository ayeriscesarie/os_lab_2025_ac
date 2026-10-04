#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс завершается
        printf("Child process: PID = %d\n", getpid());
        printf("Child process finished.\n");
        return 0;
    } else {
        // Родитель не вызывает wait()
        printf("Parent process: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
        printf("Parent is sleeping...\n");

        sleep(300);
    }

    return 0;
}