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

.PHONY: clean

all: build-lib 

build-objs:
	$(CC) $(CFLAGS) -fPIC -c $(LIBSRC) 

build-lib: build-objs
	mkdir -p $(BUILD)
	$(CC) -shared -Wl,-soname,$(LIBNAME) -o $(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILD)
	mv $(LIBNAME)* $(BUILD)
	cd $(BUILD)
	ln -sf $(LIBNAME).$(VERSION) $(BUILD)/$(LIBNAME)

test-dfs: #build-lib
	$(CC) $(CFLAGS) test/dfs.c -Isrc/ -Lbuild/ -g -ladjacency -o dfs
	
clean:
	rm -rf $(BUILD) *.o

