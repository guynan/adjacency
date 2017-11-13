#
# Adjacency Makefile, Guy Nankivell, 2017
#

# Library specific options
LIBNAME=libadjacency.so
VERSION = devel

# Avoid inheritance of shell from environment
SHELL = /bin/sh

# Clear implicit suffixes
.SUFFIXES:
.SUFFIXES: .c .o

# This is where the shared library will get copied to. If you have permission
# to write into /usr/local/lib, this is the most painless way to go about it.
# Else, if you have elevated permission but do not wish to be writing the 
# library as root whilst you are developing, edit /etc/ld.so.conf and add in
# /home/user/lib/ and as root run ldconfig. Alternatively, export the 
# LD_LIBRARY_FLAG to include ~/lib/ and then source your bashrc
LIBPREFIX = ~/lib/
#LIBPREFIX = usr/local/lib/
INCLPREFIX = ~/include/

# Prefixes for commonly used directories.
SRCDIR = src/
TESTDIR = test/
BUILDDIR = build/

# Compilation Options
CC = gcc
CFLAGS= -Wall -Wextra -pedantic 
LFLAGS= 
DEBUG= -g -pg

.PHONY: clean clean-test cp-lib set-ld

PROG = create-build-dir build-objs so-gen cp-lib cp-headers

all: $(PROG)

create-build-dir: 
	mkdir -p $(BUILDDIR)

vertex.o: src/vertex.c src/vertex.h
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c

graph.o: src/graph.c src/vertex.h
	$(CC) $(CFLAGS) -fPIC -c src/graph.c

fileutils.o: src/fileutils.c
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c

build-objs: vertex.o fileutils.o graph.o

so-gen: vertex.o fileutils.o
	$(CC) -dynamiclib -shared -Wl,-soname,$(LIBNAME) -o \
			$(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILDDIR)
	mv $(LIBNAME)* $(BUILDDIR)

cp-lib:
	mkdir -p $(LIBPREFIX)
	cp $(BUILDDIR)$(LIBNAME).$(VERSION) $(LIBPREFIX)
	ln -sf ~/lib/$(LIBNAME).$(VERSION) $(LIBPREFIX)$(LIBNAME)

cp-headers:
	mkdir -p $(INCLPREFIX)
	cp $(SRCDIR)*.h $(INCLPREFIX)
	
test-dfs: all
	$(CC) $(CFLAGS) test/dfs.c -Isrc/ -g -ladjacency -o test/dfs

test-reverse: all
	$(CC) $(CFLAGS) test/reverse.c -Isrc/ -g -ladjacency -o test/rev

set-ld:
	mkdir -p ~/lib/
	echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	. ~/.profile

clean-test: 
	rm -rf test/*.txt dfs rev

clean: clean-test
	rm -rf $(BUILDDIR) *.o

