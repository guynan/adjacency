

PROGS= rev init dfs memclean graph-init
TEST_LD = -L../build/ -ladjacency
TESTS= test-dfs test-reverse test-init test-memclean test-graph-init

all: $(TESTS)
	
test-dfs:
	$(CC) $(TEST_LD) $(CFLAGS) dfs.c -I../src/ -g -o dfs

test-reverse:
	$(CC) $(TEST_LD) $(CFLAGS) reverselist.c -I../src/ -g -o rev

test-init:
	$(CC) $(TEST_LD) $(CFLAGS) largeinit.c -I../src/ -g -o init

test-memclean:
	$(CC) $(TEST_LD) $(CFLAGS) memclean.c -I../src/ -g -o memclean

test-graph-init:
	$(CC) $(TEST_LD) $(CFLAGS) graph_init.c -I../src/ -g -o graph-init

clean:
	rm -rf $(PROGS) *.txt 

.PHONY: all clean

