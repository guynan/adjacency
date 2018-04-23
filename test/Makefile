

PROGS= rev init dfs memclean graph-init
TEST_LD = -L../build/ -ladjacency
TESTS= test-dfs test-reverse test-init test-memclean test-graph-init
CFLAGS?= -Wall -Wextra --std=c99

all: $(TESTS)
	
test-dfs:
	$(CC) $(CFLAGS) dfs.c -I../src/ -g -o dfs $(TEST_LD) 

test-reverse:
	$(CC) $(CFLAGS) reverselist.c -I../src/ -g -o rev $(TEST_LD)

test-init:
	$(CC) $(CFLAGS) largeinit.c -I../src/ -g -o init $(TEST_LD)

test-memclean:
	$(CC) $(CFLAGS) memclean.c -I../src/ -g -o memclean $(TEST_LD)

test-graph-init:
	$(CC) $(CFLAGS) graph_init.c -I../src/ -g -o graph-init $(TEST_LD)

clean:
	rm -rf $(PROGS) *.txt 

.PHONY: all clean

