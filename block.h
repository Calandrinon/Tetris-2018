#ifndef BLOCK_H
#include <stdlib.h>
#include <time.h>
#define BLOCK_H
#define BLOCK_SIZE 4
#define NUM_TYPES 5
#include "main.h"

struct Block {
        char model[BLOCK_SIZE][BLOCK_SIZE];
        int x, y, type;
};

void clear_block(struct Block*);
void t1(struct Block*);
void t2(struct Block*);
void t3(struct Block*);
void t4(struct Block*);
void t5(struct Block*);
void t6(struct Block*);
void t7(struct Block*);
void (*type[NUM_TYPES])(struct Block*);
struct Block generate_block();
void rotate_block(struct Block*);
#endif
