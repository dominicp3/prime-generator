CC=gcc
CFLAGS=-Wall -Werror=vla -Wextra -Wshadow -Wswitch-default
ASAN=-g -fsanitize=address
SEARCH=-I./include
OUT=-o ./bin/$@
COMPILE=$(CC) $(SEARCH) $(OUT) $^ $(CFLAGS) $(ASAN) -lm

all: primes

primes: src/primes.c src/bitarray.c
	$(COMPILE)
