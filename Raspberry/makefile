CC = gcc
CFLAGS  = -Wall
CFLAGS += -std=c99
CFLAGS += -lpthread
LDFLAGS =

OBJS = main.o driver_robot.o

all: main

main: $(OBJS)
	$(CC) $(OBJS:%=bin/%) -o $@ $(LDFLAGS)

tgz: main
	@echo "creation de l'archive"
	tar czvf flotain.tar.gz main

%.o: src/%.c include/%.h
	$(CC) $(CFLAGS) -c src/$< -o bin/$@


.PHONY: clean touchAll pretty
clean:
	@rm -f bin/*.o main

touchAll:
	@touch src/*.c

pretty:
	astyle *.c -A4
