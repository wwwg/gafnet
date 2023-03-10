CC=gcc

SRC=gafnet/*.c
SRC_OPTS=-lpthread -pthread -D GAFNET_DEBUG

TEST=test/*.c
TEST_OPTS=$(SRC_OPTS) -Igafnet/ -Lgafnet/
TEST_OUT=./gaftest

default:
	$(CC) $(SRC_OPTS) -c $(SRC)

test-net:
	make
	$(CC) $(TEST_OPTS) -c $(TEST)
	$(CC) $(TEST_OPTS) -o $(TEST_OUT) *.o

test-run:
	make clean
	make test-net
	./$(TEST_OUT)

clean:
	rm -f *.o