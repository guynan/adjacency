# Adjacency

A high level interface for manipulating graph theory objects in C

## About

This is designed to be a standalone library written in pure C99.

This project was initially an assignment which was supposed to be written in 
Python. I didn't really think Python was the appropriate tool so I wrote it in
C and called my makefile from the Python files.

Now, I have taken this as a little hobby project to create a comprehensive 
graph library written in C. The motif of its construction is to have access to 
a swathe of complex graph theory operations in a high level environment. It 
is purposely abstract. The idea is that the interaction between the user and 
the library is solely through the functions provided and let the rest 
'just work'. 

Currently, the graph manipulations are so simple that everything should perform
well, even for larger data sets. The current upper limit on data sets at the 
moment is governed by my csv parser which imposes a pretty low limit. This is
of course not a problem if you are inputting the data in manually through the 
interface provided. 

## Usage

As I develop, I prefer to run compile the library and be able to run binaries
without too much fuss, and definitely without the aid of privilege escalation.

If you too are of this ilk, I pose some solutions for allowing the library path
to be set. 

1. Edit `/etc/ld.so.conf` and add the directory you wish and subsequently edit
the `LIBPREFIX` variable in the Makefile to reflect your choice.

2. You can also run `make set-ld` and this will modify your `~/.profile` to be
able to set the `LD_LIBRARY_PATH` variable.

3. Modify the ownership of `/usr/local/lib/` to be able to get at it as a 
normal user and again, change the `LIBPREFIX` variable in the `Makefile`.

4. Just run everything as root and hope like fucking mad you don't do anything
stupid.


## Development Workflow

As I extend the adjacency library, I will not support any installation per se
as it is still pretty untested, nor hugely capable.

Currently, the `src` directory contains all of the code that pertains directly
to the creation of the library. 

The `test` directory contains code which links
against a compiled form of the library and tests functionality.

## Make Targets
`make` really does most of the heavy lifting here. It compiles the code in 
`src` and turns it into a shared library. 

`make test-dfs` and the other test equivalents link against `libadjacency` and
output a binary.

## Compiling against the Library
Unless you are chucking the header files into a global include directory too,
I suggest you more simply use `-I` in your compiler of choice to specify the 
header files for this project and link with `-ladjacency`

## Issues

If you do happen to run into the problem where your created test binaries claim
that the library does not exist, then simply run the aforementioned 
`make set-ld` to set up the environment variables. Once you login again (or I 
think `rehash` in csh may do the trick) you should be able to run the 
executables like every other program.



`
