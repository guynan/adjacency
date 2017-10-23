CC=gcc
CFLAGS=-Wall -Wextra -g 
LFLAGS= 
DEBUG= -pg
REVSRC= src/reverselist.c src/vertex.c src/fileutils.c
DFSSRC= src/dfs.c src/vertex.c src/fileutils.c
OUT=main
GARBAGE= reverselist.txt dfs.txt

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

