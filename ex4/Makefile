CFLAGS=-Wall -Wextra -pedantic -g -O0 -std=c99
#CPPFLAGS=
#LDFLAGS=

SRCS = insertion_sort_counter.c insertion_sort_timed.c moore.c newton.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

insertion_sort_counter: insertion_sort_counter.o
	$(CC) $(LDFLAGS) -o $@ $^

insertion_sort_timed: insertion_sort_timed.o
	$(CC) $(LDFLAGS) -o $@ $^

moore: moore.o
	$(CC) $(LDFLAGS) -o $@ $^

newton: newton.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
