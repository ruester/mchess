#COMPILING AND LINKING
CC	= gcc
CFLAGS	= -Wall -g -pedantic
LDFLAGS = -lm
OBJECTS = main.o

#PROJECT
PROJECT  = mchess
VERSION  = 0
REVISION = 1

#PACKAGE
TARDIR  = $(PROJECT)-$(VERSION).$(REVISION)
TARFILE = $(TARDIR).tar

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

package:
	rm -rf $(TARFILE) $(TARDIR) $(TARFILE).bz2
	mkdir $(TARDIR)
	cp -f *.c *.h Makefile LICENSE $(TARDIR)
	tar cf $(TARFILE) $(TARDIR)
	bzip2 -z9 $(TARFILE)
	rm -rf $(TARDIR)

clean:
	rm -f $(OBJECTS) $(PROJECT)
