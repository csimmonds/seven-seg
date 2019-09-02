# From https://dino.ciuffetti.info/2014/04/adafruit-4-digit-7-segment-backpack-raspberry-pi-in-c/

DESTDIR ?= /
BINDIR ?= usr/bin

CFLAGS=-Wall -g
PROG=seven-seg

all: $(PROG)

$(PROG): 7seg_bp_ada.o 7seg_bp_ada_test.o
	$(CC) $(LDFLAGS) 7seg_bp_ada.o 7seg_bp_ada_test.o -o $(PROG)

7seg_bp_ada.o: 7seg_bp_ada.c
       
7seg_bp_ada_test.o: 7seg_bp_ada_test.c

clean:
	rm -f *.o
	rm -f $(PROG)

install:
	install -d $(DESTDIR)/$(BINDIR)
	install -m 0755 $(PROG) $(DESTDIR)/$(BINDIR)
