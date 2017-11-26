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
CFLAGS= -Wall -Wextra -pedantic --std=c99
DEBUG_FLAGS= -Werror -Wstrict-prototypes -Wpointer-arith -Wshadow \
			 -pg -g 
#			 -fsanitise=address -fsanitize=undefined \
#

LFLAGS= 

# Flags for enabling or disabling compiler options for either strict debugging
# or allowing the debugging options to be disabled and produce faster code with
# no debugging symbols
DEBUG=1
DIST=0

ifeq ($(DEBUG), 0)
		DEBUG_FLAGS = 
endif

ifeq ($(DIST), 1)
		DEBUG_FLAGS = -O2
endif

# Crude compiler detection
#CLANG := $(shell command  -v clang --version 2> /dev/null)
#ifdef CLANG
#	CC = clang
#endif

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
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c $(DEBUG_FLAGS)

meta.o: src/meta.c src/meta.h
	$(CC) $(CFLAGS) -fPIC -c src/meta.c $(DEBUG_FLAGS)

graph.o: src/graph.c src/vertex.h src/graph.h
	$(CC) $(CFLAGS) -fPIC -c src/graph.c $(DEBUG_FLAGS)

fileutils.o: src/fileutils.c src/fileutils.h
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c $(DEBUG_FLAGS)

adjlist.o: src/adjlist.c src/adjlist.h
	$(CC) $(CFLAGS) -fPIC -c src/adjlist.c $(DEBUG_FLAGS)

build-objs: vertex.o fileutils.o graph.o meta.o adjlist.o

so-gen: build-objs
	$(CC) -dynamiclib -shared -Wl,-soname,$(LIBNAME) -o \
			$(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILDDIR)
	mv $(LIBNAME)* $(BUILDDIR)

so-gen-clang: build-objs
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

test-init: all
	$(CC) $(CFLAGS) test/largeinit.c -Isrc/ -g -ladjacency -o test/init

tests: test-dfs test-reverse test-init

set-ld:
	mkdir -p ~/lib/
	echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	echo "export LIBRARY_PATH=\$$LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	. ~/.profile

clean-test: 
	rm -rf test/*.txt test/dfs test/rev test/init

clean: clean-test
	rm -rf $(BUILDDIR) *.o

