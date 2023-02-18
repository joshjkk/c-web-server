CC = gcc
EXEC = server
SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:.c=.o)
FLAGS = -Wall -Wextra -pedantic -ggdb


$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXEC).out

%.o: %.c include/%.h
	$(CC) -c $(FLAGS) $< -o $@

clean:
	-rm *.out
	-rm src/*.o

