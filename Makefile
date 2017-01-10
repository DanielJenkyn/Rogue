CC = gcc
CFLAGS = -lmenu -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)windows/*.c\
		  $(SRCDIR)utils/*.c

all: rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -g -o $@.out

run:
	./rogue.out

clean:
	rm rogue.out