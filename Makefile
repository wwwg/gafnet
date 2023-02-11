CC=gcc

SRC=gafnet/*.c
SRC_OPTS=

TEST=test/*.c
TEST_OPTS=-Igafnet/
TEST_OUT=./gaftest

default:
	$(CC) -$(SRC_OPTS) -c $(SRC)

test-net:
	$(CC) $(TEST_OPTS) -c $(TEST)
	OBJS=*.o
	$(CC) $(TEST_OPTS) -o $(TEST_OUT) $(OBJS)

clean:
	rm *.o