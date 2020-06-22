#ifndef PRIMES_H
#define PRIMES_H

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitarray.h"

struct prime
{
        bitarray_t *nums;
        long count;
        long bound;
};

void destroy_prime(struct prime *p);
struct prime *primes(long n);
void write_to_file(struct prime *p);

#endif /* PRIMES_H */