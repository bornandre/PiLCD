IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lwiringPi

_DEPS = daemonize.h st7036.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o daemonize.o st7036.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pilcd: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean log start check

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


log:
	grep pilcd /var/log/syslog | tail

start:
	./pilcd

check:
	ps xj | head -1
	@ps xj | grep pilcd

