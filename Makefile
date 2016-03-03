#
# Makefile for lab2 in Advanced Computer Architecture.
#
# Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
# Revision (2015,2016): German Ceballos <german.ceballos@it.uu.se>
#
#
CC=gcc
CFLAGS=-std=c99 -D_XOPEN_SOURCE=600 -msse3 -O2 -Wall -Werror -g
LDFLAGS=-g
LIBS=-lpthread -lrt

TEST_IMPLS=cmpxchg critical incdec
CS_IMPLS=pthreads null dekker queue

all: lab2

lab2: lab2.o $(CS_IMPLS:%=cs_%.o) $(TEST_IMPLS:%=test_%.o)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f lab2 *.o

.PHONY: all clean
