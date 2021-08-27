CFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c99
CPPFLAGS= -D_POSIX_C_SOURCE=199309L
#LDFLAGS=

SRCS = bin_search.c merge_sort.c max_min.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

bin_search: bin_search.o
	$(CC) $(LDFLAGS) -o $@ $^

max_min: max_min.o
	$(CC) $(LDFLAGS) -o $@ $^

merge_sort: merge_sort.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(BINS)
