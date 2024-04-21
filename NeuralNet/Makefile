CC := gcc
OBJ_FLAGS := -std=c99 -O3 -march=native
OBJ_DIR := build
CFLAGS := -lm -std=c99 -Wall -Wextra

all: main

$(shell mkdir -p $(OBJ_DIR))

main: main.o pbPlots.o supportLib.o FileManagement.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/pbPlots.o $(OBJ_DIR)/supportLib.o $(OBJ_DIR)/FileManagement.o $(CFLAGS) -o main

main.o: main.c pbPlots.h supportLib.h
	gcc -c main.c -o $(OBJ_DIR)/main.o $(OBJ_FLAGS) -g

supportLib.o: supportLib.c supportLib.h
	gcc -c supportLib.c -o $(OBJ_DIR)/supportLib.o $(OBJ_FLAGS)

pbPlots.o: pbPlots.c pbPlots.h
	gcc -c pbPlots.c -o $(OBJ_DIR)/pbPlots.o $(OBJ_FLAGS)

FileManagement.o: FileManagement.c FileManagement.h
	gcc -c FileManagement.c -o $(OBJ_DIR)/FileManagement.o -std=c99

clean:
	rm -rf main raw.png regression.png $(OBJ_DIR)