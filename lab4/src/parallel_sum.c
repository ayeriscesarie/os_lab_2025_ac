#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include "utils.h"
#include "utils.h"
#include "sum.h"


void *ThreadSum(void *args) {
    struct SumArgs *sum_args = (struct SumArgs *)args;
    sum_args->sum = Sum(sum_args);
    return NULL;
}

int main(int argc, char **argv) {
  /*
   *  TODO:
   *  threads_num by command line arguments
   *  array_size by command line arguments
   *	seed by command line arguments
   */

  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;
  static struct option options[] = {
    {"threads_num", required_argument, 0, 0},
    {"seed", required_argument, 0, 0},
    {"array_size", required_argument, 0, 0},
    {0, 0, 0, 0}
};

int option_index = 0;
int option;

while ((option = getopt_long(argc, argv, "", options, &option_index)) != -1) {
    switch (option_index) {
        case 0:
            threads_num = atoi(optarg);
            break;
        case 1:
            seed = atoi(optarg);
            break;
        case 2:
            array_size = atoi(optarg);
            break;
        default:
            printf("Unknown argument\n");
            return 1;
    }
}

if (threads_num == 0 || array_size == 0) {
    printf("threads_num and array_size must be greater than 0\n");
    return 1;
}

pthread_t threads[threads_num];


  /*
   * TODO:
   * your code here
   * Generate array here
   */

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

struct timespec start, end;
clock_gettime(CLOCK_MONOTONIC, &start);

  struct SumArgs args[threads_num];

for (uint32_t i = 0; i < threads_num; i++) {
    args[i].array = array;
    args[i].begin = i * array_size / threads_num;
    args[i].end = (i + 1) * array_size / threads_num;

    if (pthread_create(&threads[i], NULL, ThreadSum, &args[i])) {
        printf("Error: pthread_create failed!\n");
        return 1;
    }
}

int64_t total_sum = 0;

for (uint32_t i = 0; i < threads_num; i++) {
    pthread_join(threads[i], NULL);
    total_sum += args[i].sum;
}
  clock_gettime(CLOCK_MONOTONIC, &end);

double elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
elapsed += (end.tv_nsec - start.tv_nsec) / 1000000.0;

printf("Total: %" PRId64 "\n", total_sum);
printf("Elapsed time: %.3f ms\n", elapsed);
  free(array);
  return 0;
}
