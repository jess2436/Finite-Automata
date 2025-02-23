CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g

SOURCES = main.c dfa.c nfa.c LinkedList.c IntHashSet.c nfaTOdfa.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = proj1

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
