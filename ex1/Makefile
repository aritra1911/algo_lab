CFLAGS=-Wall -Wextra -pedantic -g -O0 -std=c99
#CPPFLAGS=
#LDFLAGS=

SRCS=smallest_largest.c duplicate.c repeating.c even_odd.c rotate.c \
	 swap_pair.c product.c

OBJS=$(SRCS:.c=.o)
BINS=$(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

duplicate: duplicate.o
	$(CC) $(LDFLAGS) -o $@ $^

even_odd: even_odd.o
	$(CC) $(LDFLAGS) -o $@ $^

product: product.o
	$(CC) $(LDFLAGS) -o $@ $^

repeating: repeating.o
	$(CC) $(LDFLAGS) -o $@ $^

rotate: rotate.o
	$(CC) $(LDFLAGS) -o $@ $^

smallest_largest: smallest_largest.o
	$(CC) $(LDFLAGS) -o $@ $^

swap_pair: swap_pair.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(BINS)
