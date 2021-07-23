CFLAGS=-Wall -Wextra -pedantic -g -O0 -std=c99
#CPPFLAGS=
#LDFLAGS=

SRCS=smallest_largest.c duplicate.c repeating.c even_odd.c rotate.c \
	 swap_pair.c product.c

OBJS=$(SRCS:%.c=%.o)
BINS=$(SRCS:%.c=%)

.PHONY: all clean

all: $(BINS)

$(BINS): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $@.o

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(BINS)
