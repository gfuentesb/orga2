CC = gcc
ASM = nasm
DBG = gdb
CFLAGS = -ggdb -Wall -std=c99 -pedantic -m64 -fPIC -I src/
ASMFLAGS = -felf64 -g -F dwarf
OPENCV_LIB = $(shell pkg-config --cflags --libs opencv)

MAIN=tpcopados
BIN=bin

SRC=src

NFILTROS:=$(shell grep define[[:space:]]NFILTROS ${SRC}/filtros.h | awk '{print $$3}')
FILTROS:=$(shell grep filtros ${SRC}/filtros.h | awk -F\" '{for (i=2;i<NF;i+=2){printf "%s ",$$i}}')

ASMOBJS=$(patsubst %, asm/%_asm.o, ${FILTROS})
COBJS=$(patsubst %, c/%_c.o, ${FILTROS})
MOBJ=tpcopados.o utils.o

OBJS=$(patsubst %, ${BIN}/%, ${MOBJ} ${COBJS} ${ASMOBJS})

export THISDIR:=$(CURDIR)

.PHONY: all test clean clean-sources


all: $(MAIN) test

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(OPENCV_LIB) -o $@ 

$(BIN)/%_c.o: $(SRC)/%_c.c
	mkdir -p $(BIN)/c
	$(CC) $(CFLAGS) -c -o $@ $< $(OPENCV_LIB)

$(BIN)/%_asm.o: $(SRC)/%_asm.asm
	mkdir -p $(BIN)/asm
	$(ASM) $(ASMFLAGS) -o $@ $< $(OPENCV_LIB)
	
$(BIN)/%.o: $(SRC)/%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -o $@ $< $(OPENCV_LIB)
	

test:
	$(MAKE) -C ../tester/
	


clean:
	rm -rf $(MAIN)
	rm -rf $(BIN)/*
	
