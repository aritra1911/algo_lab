CFLAGS=-Wall -Wextra -pedantic -g -O0 -std=c99
#CPPFLAGS=
#LDFLAGS=

SRCS=missing.c key.c union_intersection.c matrix.c

OBJS=$(SRCS:.c=.o)
BINS=$(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

key: key.o
	$(CC) $(LDFLAGS) -o $@ $^

matrix: matrix.o
	$(CC) $(LDFLAGS) -o $@ $^

missing: missing.o
	$(CC) $(LDFLAGS) -o $@ $^

union_intersection: union_intersection.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(BINS)
