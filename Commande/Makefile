CC = gcc
CFLAGS  = -Wall
CFLAGS += -std=gnu89
CFLAGS += -lpthread
CFLAGS += -I include
CFLAGS += -lm
LDFLAGS += -L .

ifdef _DEBUG_
CFLAGS += -D_DEBUG_
LDFLAGS += -l inetdebug
endif

OBJS = commode.o matraque.o marvelmind.o serial_client.o

all: commode

commode: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(CFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean touchAll pretty
clean:
	@rm -f *.o commode

touchAll:
	@touch *.c

pretty:
	astyle *.c -A4
