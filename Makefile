CC=gcc
CFLAGS=-Wall -Wextra -g 
LFLAGS= 
DEBUG= -pg
REVSRC= reverselist.c vertex.c fileutils.c
DFSSRC= dfs.c vertex.c fileutils.c
OUT=main
GARBAGE=gmon.out

all:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(LFLAGS)

rev:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(LFLAGS)

dfs:
	$(CC) $(CFLAGS) -o $(OUT) $(DFSSRC) $(LFLAGS)

dfs-dbg:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(DEBUG) $(LFLAGS)

rev-dbg:
	$(CC) $(CFLAGS) -o $(OUT) $(REVSRC) $(DEBUG) $(LFLAGS)

run-dfs: dfs
	./$(OUT)

run-rev: dfs
	./$(OUT)

clean:
	rm $(OUT) $(GARBAGE)

