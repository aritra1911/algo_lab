CFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c99

CPPFLAGS = -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=199309L

SRCS = fractional_knapsack.c activity_selection.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

activity_selection: activity_selection.o
	$(CC) $(LDFLAGS) -o $@ $^

fractional_knapsack: fractional_knapsack.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
