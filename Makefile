# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = clean all

CC = gcc			# compiler to use
FLAGS = -Wall -Wextra

LINKERFLAG = -lm

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: install

install: 
	@echo "Checking.."
	${CC} ${FLAGS} ${SRCS} -o out

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS}
