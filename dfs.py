"""
Guy Nankivell

981308038

This is mostly not written in Python. I prefer C so this script calls 
a makefile, which compiles and runs the program. The relevant source
code can be found in src/

"""

import os


def dfs():
    
    target = "make run-dfs";
    os.system(target);

dfs();
