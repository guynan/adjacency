# Adjacency Makefile, Guy Nankivell, 2017

# 
VERSION = devel

# Avoid inheritance of shell from environment
SHELL = /bin/sh

# Clear implicit suffixes
.SUFFIXES:
.SUFFIXES: .c .o

SRCDIR= src/
TESTDIR = test/

# Compilation Options
CC = gcc
CFLAGS= -Wall -Wextra -pedantic 
LFLAGS= 
DEBUG= -g -pg

REVSRC= src/reverselist.c src/vertex.c src/fileutils.c
DFSSRC= src/dfs.c src/vertex.c src/fileutils.c
OUT=main
LIBSRC= src/vertex.c src/fileutils.c
GARBAGE= reverselist.txt dfs.txt
LIBNAME=libadjacency.so
BUILD = build

.PHONY: clean clean-test cp-lib

PROG = create-build-dir build-objs so-gen cp-lib

all: $(PROG)

create-build-dir: 
	mkdir -p $(BUILD)

vertex.o: src/vertex.c src/vertex.h
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c

fileutils.o: src/fileutils.c
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c

build-objs: vertex.o fileutils.o

so-gen: vertex.o fileutils.o
	$(CC) -shared -Wl,-soname,$(LIBNAME) -o $(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILD)
	mv $(LIBNAME)* $(BUILD)

cp-lib:
	mkdir -p ~/lib/
	cp $(BUILD)/$(LIBNAME).$(VERSION) ~/lib/
	ln -sf ~/lib/$(LIBNAME).$(VERSION) ~/lib/$(LIBNAME)
	
#build-lib: create-build-dir build-objs
#	cd $(BUILD)
#	ln -sf $(LIBNAME).$(VERSION) $(BUILD)/$(LIBNAME)

test-dfs: all
	$(CC) $(CFLAGS) test/dfs.c -Isrc/ -Lbuild/ -g -ladjacency -o test/dfs

test-reverse: all
	$(CC) $(CFLAGS) test/reverse.c -Isrc/ -Lbuild/ -g -ladjacency -o test/rev

clean-test: 
	rm -rf test/*.txt dfs rev


# This is a bit of a cheap way of doing it.
# To use the lib directory in home, you can either export the LD_LIBRARY_PATH
# or edit /etc/ld.so.conf && ldconfig as root. Temporary solution so I can
# speed up debuggind time
	
clean:
	rm -rf $(BUILD) *.o

