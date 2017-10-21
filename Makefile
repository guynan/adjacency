CC=gcc
CFLAGS=-Wall -Wextra -g
LFLAGS=
REVSRC= reverselist.c vertex.c fileutils.c
DFSSRC= dfs.c vertex.c fileutils.c
OUT=main

all:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(LFLAGS)

dfs:
	$(CC) $(CFLAGS) -o $(OUT) $(DFSSRC) $(LFLAGS)

run: all
	./$(OUT)

clean:
	rm $(OUT) out.txt

