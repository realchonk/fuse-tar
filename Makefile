CC=gcc
CFLAGS += -g -Og -std=c11 -D_XOPEN_SOURCE=700 -D_FILE_OFFSET_BITS=64 -Iinclude -Wall -Wextra
LIBS=-lfuse

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

.PHONY: all clean test
