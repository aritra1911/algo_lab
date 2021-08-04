CFLAGS=-Wall -Wextra -pedantic -g -O0 -std=c99
#CPPFLAGS=
LDFLAGS=-lm

SRCS=prime.c gcd.c

OBJS=$(SRCS:.c=.o)
BINS=$(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

gcd: gcd.o
	$(CC) $(LDFLAGS) -o $@ $^

prime: prime.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
