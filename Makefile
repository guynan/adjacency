CC=gcc
CFLAGS=-Wall -Wextra -g
LFLAGS=
SRC= reverselist.c vertex.c fileutils.c
OUT=main

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LFLAGS)

run: all
	./$(OUT)

clean:
	rm $(OUT)

