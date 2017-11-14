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
#CC = clang
CFLAGS= -Wall -Wextra -pedantic 
LFLAGS= 
DEBUG= -g -pg

.PHONY: clean clean-test cp-lib set-ld

PROG = create-build-dir so-gen cp-lib cp-headers

# Dumb way of passing the correct compiler options
ifeq ($(CC),clang)
	PROG = create-build-dir so-gen-clang cp-lib cp-headers
endif

all: $(PROG)

create-build-dir: 
	mkdir -p $(BUILDDIR)

# Object files for dependency checks at compile time
vertex.o: src/vertex.c src/vertex.h src/meta.h
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c

meta.o: src/meta.c src/meta.h
	$(CC) $(CFLAGS) -fPIC -c src/meta.c

graph.o: src/graph.c src/vertex.h src/graph.h
	$(CC) $(CFLAGS) -fPIC -c src/graph.c

fileutils.o: src/fileutils.c src/fileutils.h
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c

adjlist.o: src/adjlist.c src/adjlist.h
	$(CC) $(CFLAGS) -fPIC -c src/adjlist.c

build-objs: vertex.o fileutils.o graph.o meta.o adjlist.o

so-gen: build-objs
	$(CC) -dynamiclib -shared -Wl,-soname,$(LIBNAME) -o \
			$(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILDDIR)
	mv $(LIBNAME)* $(BUILDDIR)

so-gen-clang: vertex.o fileutils.o
	$(CC) -dynamiclib -shared -Wl,-install_name,$(LIBNAME) -o \
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
	$(CC) $(CFLAGS) test/reverselist.c -Isrc/ -g -ladjacency -o test/rev

set-ld:
	mkdir -p ~/lib/
	echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	. ~/.profile

clean-test: 
	rm -rf test/*.txt test/dfs test/rev

clean: clean-test
	rm -rf $(BUILDDIR) *.o

