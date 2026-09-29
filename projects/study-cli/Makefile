CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion \
         -Wshadow -Wstrict-prototypes -g3 -O0 -fno-omit-frame-pointer

study: main.o record.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c record.h
record.o: record.c record.h

clean:
	rm -f study *.o

.PHONY: clean
