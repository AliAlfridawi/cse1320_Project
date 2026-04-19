CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = bakery_system.exe
SRC_DIR = src
OBJ_DIR = obj

SRCS = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/inventory.c \
    $(SRC_DIR)/menu.c \
    $(SRC_DIR)/cart.c \
    $(SRC_DIR)/storage.c

OBJS = \
    $(OBJ_DIR)/main.o \
    $(OBJ_DIR)/inventory.o \
    $(OBJ_DIR)/menu.o \
    $(OBJ_DIR)/cart.o \
    $(OBJ_DIR)/storage.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/common.h $(SRC_DIR)/inventory.h $(SRC_DIR)/menu.h $(SRC_DIR)/cart.h $(SRC_DIR)/storage.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory.o: $(SRC_DIR)/inventory.c $(SRC_DIR)/inventory.h $(SRC_DIR)/common.h $(SRC_DIR)/storage.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.c $(SRC_DIR)/menu.h $(SRC_DIR)/common.h $(SRC_DIR)/storage.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/cart.o: $(SRC_DIR)/cart.c $(SRC_DIR)/cart.h $(SRC_DIR)/menu.h $(SRC_DIR)/common.h $(SRC_DIR)/storage.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/storage.o: $(SRC_DIR)/storage.c $(SRC_DIR)/storage.h $(SRC_DIR)/inventory.h $(SRC_DIR)/menu.h $(SRC_DIR)/cart.h $(SRC_DIR)/common.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

run: $(TARGET)
	.\$(TARGET)

clean:
	if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	if exist "$(TARGET)" del "$(TARGET)"

rebuild: clean all

.PHONY: all run clean rebuild
