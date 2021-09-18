LIBS_QS = -lpthread

CFLAGS = -Wall -Wextra -pedantic -g -O3 -std=c99

CPPFLAGS = -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=199309L \
           -D_POSIX_THREAD_ATTR_STACKSIZE

LDFLAGS_QS = $(LDFLAGS) $(LIBS_QS)

SRCS = quick_sort.c guess_game.c social.c new_sort.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

guess_game: guess_game.o
	$(CC) -o $@ $^

new_sort: new_sort.o
	$(CC) $(LDFLAGS) -o $@ $^

quick_sort: quick_sort.o
	$(CC) $(LDFLAGS_QS) -o $@ $^

social: social.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
