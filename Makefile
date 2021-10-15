# Raduta Lavinia-Maria 313CA 2021
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=main

build: $(TARGETS)

main: galactic_war.c
	$(CC) $(CFLAGS) galactic_war.c functions.c CircularDoublyLinkedList.c -o main -g

clean:
	rm -f $(TARGETS)

.PHONY: clean
