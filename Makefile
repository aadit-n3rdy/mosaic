CC=clang
CFLAGS=-Wall
.PHONY = clean all

all: libmosaic.a test

libmosaic.a: mosaic.o
	ar rcs libmosaic.a mosaic.o

mosaic.o: src/mosaic.c src/mosaic.h
	${CC} ${CFLAGS} -c -o mosaic.o src/mosaic.c

test: libmosaic.a src/test.c
	${CC} ${CFLAGS} -o test -L. src/test.c -lmosaic
clean:
	--	rm *.o
	--	rm libmosaic.a
	--	rm test

