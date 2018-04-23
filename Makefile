#
# Adjacency Makefile, Guy Nankivell, 2017
#

# Library specific options
CC ?= gcc
NAME = adjacency
LIBNAME=libadjacency.so
VERSION = devel
PREFIX?=~

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
LIBPREFIX = $(PREFIX)/lib/
INCLPREFIX = $(PREFIX)/include/

LIBINSTALL = /usr/local/lib/
INCLINSTALL = /usr/local/include/

# Prefixes for commonly used directories.
SRCDIR = src/
OBJDIR = obj/
TESTDIR = test/
BUILDDIR = build/


#
# Compilation Options
#

CFLAGS = -Wall -Wextra --std=c99
DEBUG_FLAGS = -Werror -Wstrict-prototypes -Wpointer-arith -Wshadow \
			 -pg -g 

LFLAGS= 

# Flags for enabling or disabling compiler options for either strict debugging
# or allowing the debugging options to be disabled and produce faster code with
# no debugging symbols. Note: DIST overrides DEBUG

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

# 
# Object files for dependency checks at compile time
#

memutils.o:
	$(CC) $(CFLAGS) -fPIC -c src/memutils.c $(DEBUG_FLAGS) $(LFLAGS)

vertex.o:
	$(CC) $(CFLAGS) -fPIC -c src/vertex.c $(DEBUG_FLAGS) $(LFLAGS)

meta.o:
	$(CC) $(CFLAGS) -fPIC -c src/meta.c $(DEBUG_FLAGS) $(LFLAGS)

graph.o:
	$(CC) $(CFLAGS) -fPIC -c src/graph.c $(DEBUG_FLAGS) $(LFLAGS)

fileutils.o:
	$(CC) $(CFLAGS) -fPIC -c src/fileutils.c $(DEBUG_FLAGS) $(LFLAGS)

adjlist.o:
	$(CC) $(CFLAGS) -fPIC -c src/adjlist.c $(DEBUG_FLAGS) $(LFLAGS)


build-objs: vertex.o fileutils.o graph.o meta.o adjlist.o memutils.o

#
# Build the Library
#

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
	ln -sf $(LIBPREFIX)/$(LIBNAME).$(VERSION) $(LIBPREFIX)$(LIBNAME)

cp-headers:
	mkdir -p $(INCLPREFIX)
	cp $(SRCDIR)*.h $(INCLPREFIX)

#
# Install
#

install: create-build-dir so-gen
	mkdir -p $(LIBINSTALL)
	mkdir -p $(INCLINSTALL)/$(NAME)/
	cp $(BUILDDIR)$(LIBNAME).$(VERSION) $(LIBINSTALL)
	ln -sf $(LIBINSTALL)/$(LIBNAME).$(VERSION) $(LIBINSTALL)$(LIBNAME)
	cp $(SRCDIR)*.h $(INCLINSTALL)/$(NAME)/

uninstall:
	rm -rf $(LIBINSTALL)/$(LIBNAME)*
	rm -rf $(INCLINSTALL)/$(NAME)/
	

#
# Test Targets
#

TEST_LD = -ladjacency
	
test-dfs: all
	$(CC) $(CFLAGS) test/dfs.c -Isrc/ -g -o test/dfs $(TEST_LD)

test-reverse: all
	$(CC) $(CFLAGS) test/reverselist.c -Isrc/ -g -o test/rev $(TEST_LD)

test-init: all
	$(CC) $(CFLAGS) test/largeinit.c -Isrc/ -g -o test/init $(TEST_LD)

test-memclean: all
	$(CC) $(CFLAGS) test/memclean.c -Isrc/ -g -o test/memclean $(TEST_LD)

test-graph-init:
	$(CC) $(CFLAGS) test/graph_init.c -Isrc/ -g -o test/graph-init $(TEST_LD)

tests: test-dfs test-reverse test-init test-memclean test-graph-init

#
# Clean Targets
#

clean-test: 
	rm -rf test/*.txt test/dfs test/rev test/init test/memclean test/graph-init

clean: clean-test
	rm -rf $(BUILDDIR) *.o

#
# One time use to set the LIBRARY PATH
#

set-ld:
	mkdir -p ~/lib/
	echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	echo "export LIBRARY_PATH=\$$LIBRARY_PATH:$(LIBPREFIX)" >> \
			~/.profile
	. ~/.profile

