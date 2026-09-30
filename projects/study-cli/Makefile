CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion \
         -Wshadow -Wstrict-prototypes -g3 -O0 -fno-omit-frame-pointer

study: main.o record.o storage.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c record.h storage.h
record.o: record.c record.h
storage.o: storage.c storage.h

clean:
	rm -f study *.o

.PHONY: clean
