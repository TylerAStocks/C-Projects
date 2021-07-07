CC = gcc
CFLAGS = -Wall -std=c99 -g -D_GNU_SOURCE
LDLIBS = -lm


all: encode decode

encode: encode.o j10.o bits.o image.o
decode: decode.o j10.o bits.o image.o

encode.o: encode.c j10.h
decode.o: decode.c j10.h
j10.o: j10.c bits.h image.h j10.h
bits.o: bits.c bits.h
image.o: image.c image.h

clean:
	rm -f *.o
	rm -f encode decode