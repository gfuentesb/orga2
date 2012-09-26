CC = gcc
ASM = nasm
DBG = gdb
CFLAGS = -ggdb -Wall -std=c99 -pedantic -m64
ASMFLAGS = -felf64 -g -F dwarf
OPENCV_LIB = `pkg-config --cflags --libs opencv`

BIN = tp2
BIN_DIR = ../bin

OBJS = tp2.o utils.o \
	recortar_c.o recortar_asm.o \
	pixelar_c.o pixelar_asm.o \
	combinar_c.o combinar_asm.o \
	monocromatizar_inf_c.o monocromatizar_inf_asm.o \
	monocromatizar_uno_c.o monocromatizar_uno_asm.o \
	normalizar_local_c.o normalizar_local_asm.o \
	ondas_c.o ondas_asm.o

.PHONY: all clean

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(OPENCV_LIB)
	cp $(BIN) $(BIN_DIR)/$(BIN)

tp2.o: tp2.c
	$(CC) $(CFLAGS) -c -o $@ $< $(OPENCV_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -lm

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

all: $(BIN)

clean:
	rm -f $(OBJS)
	rm -f ./$(BIN)
	rm -f $(BIN_DIR)/$(BIN)
