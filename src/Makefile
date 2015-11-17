CC = gcc
CFLAGS = -g -Wall -Wextra -rdynamic -fPIC
EXTRA = -DDEBUG
LIBS = -lm

PREFIX = /usr/local

TARGET =
OBJECTS = bmp.o msg.o

ifeq ($(OS),Windows_NT)
	TARGET = libbmp.dll
	CCFLAGS += -D WIN32

	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CCFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CCFLAGS += -D IA32
    endif
else
	TARGET = libbmp.so
    UNAME_S := $(shell uname -s)

    ifeq ($(UNAME_S),Linux)
		CCFLAGS += -D LINUX
		# recipe
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
		# recipe
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
		# recipe
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
		# recipe
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
		# recipe
    endif
endif

all: $(TARGET)

test:
	$(MAKE) -C test all

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o ../$@ $(OBJECTS) $(LIBS)

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) $(EXTRA) -c bmp.c

msg.o: msg.c msg.h
	$(CC) $(CFLAGS) $(EXTRA) -c msg.c

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

.PHONY: all clean install uninstall test
