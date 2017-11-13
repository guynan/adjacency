# Adjacency Makefile, Guy Nankivell, 2017

# Library specific options
LIBNAME=libadjacency.so
VERSION = devel

# Avoid inheritance of shell from environment
SHELL = /bin/sh

# Clear implicit suffixes
.SUFFIXES:
.SUFFIXES: .c .o

# Prefixes for commonly used directories.
SRCDIR= src/
TESTDIR = test/
BUILDDIR = build/

# Compilation Options
CC = gcc
CFLAGS= -Wall -Wextra -pedantic 
LFLAGS= 
DEBUG= -g -pg

.PHONY: clean clean-test cp-lib

PROG = create-build-dir build-objs so-gen cp-lib

all: $(PROG)

create-build-dir: 
	mkdir -p $(BUILDDIR)

vertex.o: src/vertex.c src/vertex.h
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c

fileutils.o: src/fileutils.c
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c

build-objs: vertex.o fileutils.o

so-gen: vertex.o fileutils.o
	$(CC) -shared -Wl,-soname,$(LIBNAME) -o $(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILDDIR)
	mv $(LIBNAME)* $(BUILDDIR)

# This is a bit of a cheap way of doing it.
# To use the lib directory in home, you can either export the LD_LIBRARY_PATH
# or edit /etc/ld.so.conf && ldconfig as root. Temporary solution so I can
# speed up debuggind time
cp-lib:
	mkdir -p ~/lib/
	cp $(BUILDDIR)/$(LIBNAME).$(VERSION) ~/lib/
	ln -sf ~/lib/$(LIBNAME).$(VERSION) ~/lib/$(LIBNAME)
	
test-dfs: all
	$(CC) $(CFLAGS) test/dfs.c -Isrc/ -Lbuild/ -g -ladjacency -o test/dfs

test-reverse: all
	$(CC) $(CFLAGS) test/reverse.c -Isrc/ -Lbuild/ -g -ladjacency -o test/rev

clean-test: 
	rm -rf test/*.txt dfs rev

clean: clean-test
	rm -rf $(BUILDDIR) *.o

