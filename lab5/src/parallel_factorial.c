#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long long result = 1;

struct ThreadArgs {
    int begin;
    int end;
};

void *calculate_factorial(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

    long long local_result = 1;

    for (int i = args->begin; i <= args->end; i++) {
        local_result *= i;
    }

    pthread_mutex_lock(&mutex);
    result *= local_result;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char **argv) {
    int k = 0;
    int pnum = 0;
    int mod = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--pnum") == 0) {
            pnum = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--mod") == 0) {
            mod = atoi(argv[++i]);
        }
    }

    pthread_t threads[pnum];
    struct ThreadArgs args[pnum];

    for (int i = 0; i < pnum; i++) {
        args[i].begin = i * k / pnum + 1;
        args[i].end = (i + 1) * k / pnum;

        pthread_create(&threads[i], NULL, calculate_factorial, &args[i]);
    }

    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    result %= mod;

    printf("%d! mod %d = %lld\n", k, mod, result);

    return 0;
}