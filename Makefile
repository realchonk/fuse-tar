CC=gcc
CFLAGS += -g -Og -std=c11 -D_XOPEN_SOURCE=700 -D_FILE_OFFSET_BITS=64 -Iinclude -Wall -Wextra
LIBS=-lfuse

DESTDIR ?= /usr/local
XAPPDIR ?= /usr/share/applications

objects=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))

all: fuse_tar

fuse_tar: obj $(objects)
	$(CC) -o $@ $(objects) $(LIBS)

obj:
	mkdir -p obj

obj/%.o: src/%.c include
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf obj mp

test: fuse_tar
	mkdir -p mp
	./fuse_tar -d -s -f archive.tar.gz mp

install:
	install -m755 fuse_tar $(DESTDIR)/bin/fuse_tar

install-mounter:
	install -m755 src/tar-mounter.sh $(DESTDIR)/bin/tar-mounter
	install -m644 src/tar-mounter.desktop $(XAPPDIR)/tar-mounter.desktop

.PHONY: all clean test install install-mounter
