LIBS = -lpthread

CFLAGS = -Wall -Wextra -pedantic -g -O3 -std=c99
CPPFLAGS= -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=199309L \
          -D_POSIX_THREAD_ATTR_STACKSIZE
LDFLAGS = $(LIBS)

SRCS = quick_sort.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

quick_sort: quick_sort.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
