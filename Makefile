CC=gcc
CFLAGS=-Wall -Wextra -g 
LFLAGS= -pg
REVSRC= reverselist.c vertex.c fileutils.c
DFSSRC= dfs.c vertex.c fileutils.c
OUT=main
GARBAGE=gmon.out

all:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(LFLAGS)

dfs:
	$(CC) $(CFLAGS) -o $(OUT) $(DFSSRC) $(LFLAGS)

run: all
	./$(OUT)

clean:
	rm $(OUT) $(GARBAGE)

