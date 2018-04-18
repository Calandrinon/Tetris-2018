OBJS = main.c block.c

CC = gcc

OBJ_NAME = tetris

all: $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME)
