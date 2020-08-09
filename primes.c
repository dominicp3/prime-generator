#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bitarray.h>

struct prime
{
        bitarray_t *nums;
        long count;
        long bound;
};

void destroy_prime(struct prime *p);
struct prime *primes(long n);
void write_to_file(struct prime *p);

int main(int argc, char **argv)
{
        if (argc != 2) {
                printf("%s <n primes>\n", argv[0]);
                return 0;
        }

        long n_primes = strtol(argv[1], NULL, 10);

        clock_t begin = clock();
        struct prime *p = primes(n_primes);
        clock_t end = clock();

        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("\nTime: %f seconds\n\n", time_spent);

        write_to_file(p);

        destroy_prime(p);
        return 0;
}

void destroy_prime(struct prime *p)
{
        ba_destroy(p->nums);
        free(p);
}

struct prime *primes(long n)
{
        long bound;
        if (n < 6)
                bound = 10;
        else
                bound = n * (log(n) + log(log(n)));
        bitarray_t *nums = ba_init(bound + 1);
        ba_set_all(nums);

        long count = bound - 1;

        for (long k = 2; 2 * k < bound; k++) {
                ba_clear_bit(nums, 2 * k);
                count--;
        }

        long sq = (long) sqrt(bound) + 1;
        for (long p = 3; p < sq; p += 2) {
                if (ba_get_bit(nums, p) == 1) {
                        for (long k = 2; k * p < bound; k++) {
                                if (ba_get_bit(nums, k * p) == 1) {
                                        ba_clear_bit(nums, k * p);
                                        count--;
                                }
                        }
                }
        }

        struct prime *x = malloc(sizeof *x);
        x->nums = nums;
        x->count = count;
        x->bound = bound + 1;
        return x;
}

void write_to_file(struct prime *pr)
{
        char buf[100];
        sprintf(buf, "%ld_primes.txt", pr->count - 1);
        FILE *file = fopen(buf, "wb");

        strcpy(buf, "1 2\n");
        fwrite(buf, 4, 1, file);

        long p = 3;
        long i = 2;

        while (i < pr->count && p < pr->bound) {
                if (ba_get_bit(pr->nums, p) == 1) {
                        sprintf(buf, "%ld %ld\n", i, p);
                        fwrite(buf, strlen(buf), 1, file);
                        i++;
                }
                p += 2;
        }

        fclose(file);
}
