# Makefile para o projeto EDA - Fase 2

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = .
GRAFOS_DIR = Grafos

SRCS = \
	$(SRC_DIR)/main.c \
	$(GRAFOS_DIR)/grafos.c

TARGET = programa

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@if exist $(TARGET).exe del /Q /F $(TARGET).exe

.PHONY: all clean

# Para compilar: mingw32-make
# Para limpar depois o que foi compilado:   mingw32-make clean