#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>

typedef struct bitarray_t bitarray_t;

bitarray_t *ba_init(long initial_size);
int ba_set_bit(bitarray_t *b, long index);
int ba_set_all(bitarray_t *b);
int ba_clear_bit(bitarray_t *b, long index);
int ba_clear_all(bitarray_t *b);
int ba_flip_bit(bitarray_t *b, long index);
char ba_get(bitarray_t *b, long index);
long ba_size(bitarray_t *b);
void ba_destroy(bitarray_t *b);

#endif /* BITARRAY_H */