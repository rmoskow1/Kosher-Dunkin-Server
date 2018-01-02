CC = gcc

CSAPP_INC = ../../../include
CSAPP_SRC = ../../../src

CFLAGS = -Wall -O2 -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	echo.o\
        first_draft.c\
        first_draft\
	dd2hex\
	hex2dd\
	hostinfo\
	hostinfo-ntop\
	tiny/tiny\
	netpfragments.o\

all: $(CSAPP_SRC)/csapp.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/csapp.o
$(CSAPP_SRC)/csapp.o: $(CSAPP_SRC)/csapp.c $(CSAPP_INC)/csapp.h

../tiny: ../tiny.c
	(cd .. ; make)	

 
tinytarfile:
	(cd tiny; make clean)
	tar cvf - tiny >tiny.tar

clean:
	rm -f $(PROGS) *.o *~
	(cd tiny; make clean)
