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
interface provided. Eventually there will be 

