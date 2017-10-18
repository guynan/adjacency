CC=gcc
CFLAGS=-Wall -Wextra 
LFLAGS=
SRC= reverselist.c vertex.c fileutils.c
OUT=main

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LFLAGS)

clean:
	rm $(OUT)

