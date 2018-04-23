#
# Adjacency Makefile, Guy Nankivell, 2017
#

# Library specific options
CC ?= gcc
NAME = adjacency
LIBNAME=libadjacency.so
VERSION = devel
PREFIX?=~
MAKE += --no-print-directory

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
LIBPREFIX = $(PREFIX)/lib
INCLPREFIX = $(PREFIX)/include

LIBINSTALL = $(PREFIX)/lib
INCLINSTALL = $(PREFIX)/include

# Prefixes for commonly used directories.
SRCDIR = src/
OBJDIR = obj/
TESTDIR = test/
BUILDDIR = build


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

all: $(PROG) tests

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
	ln -sf $(LIBNAME).$(VERSION) $(LIBNAME)
	mv $(LIBNAME)* $(BUILDDIR)

so-gen-clang: build-objs
	$(CC) -dynamiclib -shared -Wl,-install_name,$(LIBNAME) -o \
			$(LIBNAME).$(VERSION) *.o
	mv *.o $(BUILDDIR)
	ln -sf $(LIBNAME).$(VERSION) $(LIBNAME)
	mv $(LIBNAME)* $(BUILDDIR)

cp-lib:
	mkdir -p $(LIBPREFIX)
	cp $(BUILDDIR)/$(LIBNAME).$(VERSION) $(LIBPREFIX)
	ln -sf $(LIBPREFIX)/$(LIBNAME).$(VERSION) $(LIBPREFIX)/$(LIBNAME)

cp-headers:
	mkdir -p $(INCLPREFIX)
	cp $(SRCDIR)*.h $(INCLPREFIX)

#
# Install
#

install: create-build-dir so-gen
	mkdir -p $(LIBINSTALL)
	mkdir -p $(INCLINSTALL)/$(NAME)/
	cp $(BUILDDIR)/$(LIBNAME).$(VERSION) $(LIBINSTALL)
	ln -sf $(LIBINSTALL)/$(LIBNAME).$(VERSION) $(LIBINSTALL)/$(LIBNAME)
	cp $(SRCDIR)*.h $(INCLINSTALL)/$(NAME)/

uninstall:
	rm -rf $(LIBINSTALL)/$(LIBNAME)*
	rm -rf $(INCLINSTALL)/$(NAME)/
	

#
# Test Targets
#

tests:
	$(MAKE) -C test

#
# Clean Targets
#

clean: clean-test
	rm -rf $(BUILDDIR) *.o
	$(MAKE) -C test clean

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

