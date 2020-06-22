#include "bitarray.h"

struct bitarray_t
{
        int *bits;
        long size;
};

bitarray_t *ba_init(long initial_size)
{
        bitarray_t *b = malloc(sizeof *b);
        b->size = (initial_size % 32 == 0) ? initial_size / 32 : (initial_size / 32) + 1;
        b->bits = malloc(b->size * sizeof *b->bits);
        return b;
}

int ba_set_bit(bitarray_t *b, long index)
{
        long i = index / 32;
        if (!b || index < 0 || i >= b->size)
                return -1;
        b->bits[i] |= 1 << (index % 32);
        return 0;
}

int ba_set_all(bitarray_t *b)
{
        if (!b)
                return -1;
        for (long i = 0; i < b->size; i++)
                b->bits[i] = ~0;
        return 0;
}

int ba_clear_bit(bitarray_t *b, long index)
{
        long i = index / 32;
        if (!b || index < 0 || i >= b->size)
                return -1;
        b->bits[i] &= ~(1 << (index % 32));
        return 0;
}

int ba_clear_all(bitarray_t *b)
{
        if (!b)
                return -1;
        for (long i = 0; i < b->size; i++)
                b->bits[i] = 0;
        return 0;
}

int ba_flip_bit(bitarray_t *b, long index)
{
        long i = index / 32;
        if (!b || index < 0 || i >= b->size)
                return -1;
        b->bits[i] ^= 1 << (index % 32);
        return 0;
}

char ba_get(bitarray_t *b, long index)
{
        long i = index / 32;
        if (!b || index < 0 || i >= b->size)
                return -1;
        return (b->bits[i] >> (index % 32)) & 1;
}

long ba_size(bitarray_t *b)
{
        return 8 * b->size;
}

void ba_destroy(bitarray_t *b)
{
        if (!b)
                return;
        free(b->bits);
        free(b);
}