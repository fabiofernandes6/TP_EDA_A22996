# Makefile para o projeto EDA - Fase 1 no Windows com mingw32-make

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = .
ANTENAS_DIR = ListaAntenas
NEFASTOS_DIR = EfeitosNefastos

SRCS = \
	$(SRC_DIR)/main.c \
	$(ANTENAS_DIR)/antenas.c \
	$(NEFASTOS_DIR)/nefastos.c

TARGET = programa

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@if exist $(TARGET).exe del /Q /F $(TARGET).exe

.PHONY: all clean

# Para compilar: mingw32-make
# Para limpar depois o que foi compilado:   mingw32-make clean