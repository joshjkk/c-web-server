EXEC = webserver
SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:.c=.o)
FLAGS = -Wall -Wextra -pedantic -ggdb


$(EXEC): $(OBJS)
	gcc $(OBJS) $(FLAGS) -o $(EXEC).out

%.o: %.c include/%.h
	gcc -c $(FLAGS) $< -o $@

install:
	make
	cp ./$(EXEC).out /usr/local/bin/$(EXEC)

uninstall:
	rm /usr/local/bin/$(EXEC)

clean:
	-rm *.out
	-rm src/*.o

