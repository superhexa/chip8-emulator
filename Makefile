CC = gcc
CFLAGS = -Wall -Wextra -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
INCLUDES = -Iinclude
SRC_DIR = src
OBJ_DIR = build
BIN = chip8

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(OBJ_DIR) $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

run: all
	./$(BIN) assets/roms/pong.ch8

clean:
	rm -rf $(OBJ_DIR) $(BIN)
