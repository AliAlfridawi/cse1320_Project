CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = bakery_system

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	if not exist "$(OBJ_DIR)" mkdir $(OBJ_DIR)

clean:
	if exist "$(OBJ_DIR)" rmdir /s /q $(OBJ_DIR)
	if exist "$(TARGET).exe" del $(TARGET).exe

.PHONY: all clean
