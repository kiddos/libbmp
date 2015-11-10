CC = gcc
CFLAGS = -g -Wall -Wextra -rdynamic
EXTRA = -fPIC -fopenmp -fpthread
LIBS = -lm

PREFIX = /usr/local

TARGET = test_bmp
OBJECTS = test.o bmp.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

test.o: test.c bmp.h
	$(CC) $(CFLAGS) -c test.c

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c

# cleaner
clean:
	rm -f *.o $(TARGET)

# install
install: all
	install -d $(DESTDIR)/$(PREFIX)/bin
	install $(TARGET) $(DESTDIR)/$(PREFIX)/bin

# uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

.PHONY:
	all clean install uninstall

