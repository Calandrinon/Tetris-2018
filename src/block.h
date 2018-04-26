#ifndef BLOCK_H
#include <stdlib.h>
#include <time.h>
#define BLOCK_H
#define MAX_BLOCK_SIZE 5
#define NUM_TYPES 5
#include "main.h"

struct Block {
        int x, y, type, size;
        char model[MAX_BLOCK_SIZE][MAX_BLOCK_SIZE];
};

void clear_block(struct Block*);
void t1(struct Block*);
void t2(struct Block*);
void t3(struct Block*);
void t4(struct Block*);
void t5(struct Block*);
void (*type[NUM_TYPES])(struct Block*);
struct Block generate_block();
void rotate_block(struct Block*);
char screen[SCREEN_H][SCREEN_W];
#endif
