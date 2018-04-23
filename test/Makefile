

PROGS= rev init dfs memclean graph-init
TEST_LD = -ladjacency
TESTS= test-dfs test-reverse test-init test-memclean test-graph-init

all: $(TESTS)
	
test-dfs:
	$(CC) $(CFLAGS) dfs.c -Isrc/ -g -o dfs $(TEST_LD)

test-reverse:
	$(CC) $(CFLAGS) reverselist.c -Isrc/ -g -o rev $(TEST_LD)

test-init:
	$(CC) $(CFLAGS) largeinit.c -Isrc/ -g -o init $(TEST_LD)

test-memclean:
	$(CC) $(CFLAGS) memclean.c -Isrc/ -g -o memclean $(TEST_LD)

test-graph-init:
	$(CC) $(CFLAGS) graph_init.c -Isrc/ -g -o graph-init $(TEST_LD)

clean:
	rm -rf $(PROGS) *.txt 

.PHONY: all clean

