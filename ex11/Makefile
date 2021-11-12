CFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c99

CPPFLAGS = -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=199309L

SRCS = bfs.c dfs.c dijkstra.c floyd_warshall.c dfs_reachable.c

OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(BINS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# a one-liner to generate the following nightmare
# ls -1 *.c | sed 's/\.c//g' | awk '{ print $1 ": " $1 ".o\n\t$(CC) $(LDFLAGS) -o $@ $^\n" }'

bfs: bfs.o
	$(CC) $(LDFLAGS) -o $@ $^

dfs: dfs.o
	$(CC) $(LDFLAGS) -o $@ $^

dfs_reachable: dfs_reachable.o
	$(CC) $(LDFLAGS) -o $@ $^

dijkstra: dijkstra.o
	$(CC) $(LDFLAGS) -o $@ $^

floyd_warshall: floyd_warshall.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS) $(BINS)
