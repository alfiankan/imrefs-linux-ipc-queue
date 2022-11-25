CC  = g++
CFLAGS  = -I. -Wall

all: imrefs clean

imrefs: imrefs.o
	$(CC) -o $@ $^
	chmod 700 imrefs
	mv imrefs dist/imrefs

imrefs.o: imrefs.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o
