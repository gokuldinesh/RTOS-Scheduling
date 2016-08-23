#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void *isPrime(void *);
void *prime(void *);
int parent();