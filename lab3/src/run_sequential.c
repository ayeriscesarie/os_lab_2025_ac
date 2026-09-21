#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        execl("./sequential_min_max",
              "sequential_min_max",
              "--seed", "10",
              "--array_size", "20",
              NULL);

        perror("execl");
        return 1;
    }

    wait(NULL);

    return 0;
}