CFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c99
CXXFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c++11

.PHONY: all clean

all: exp lcs

exp.o: exp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

lcs.o: lcs.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

exp: exp.o
	$(CC) $(LDFLAGS) -o $@ $^

lcs: lcs.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	rm -rf lcs.o exp.o lcs exp
