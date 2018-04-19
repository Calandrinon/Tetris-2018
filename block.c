#include <stdio.h>
#include "block.h"

void clear_block(struct Block* block) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++)
                        block->model[i][j] = ' ';
        }
}

void t1(struct Block* block) {
        clear_block(block);
        block->model[3][0] = 'I';
        block->model[3][1] = 'I';
        block->model[3][2] = 'I';
        block->model[3][3] = 'I';
}

void t2(struct Block* block) {
        clear_block(block);
        block->model[2][0] = 'L';
        block->model[3][0] = 'L';
        block->model[3][1] = 'L';
        block->model[3][2] = 'L';
}

void t3(struct Block* block) {
        clear_block(block);
        block->model[2][0] = 'O';
        block->model[2][1] = 'O';
        block->model[3][0] = 'O';
        block->model[3][1] = 'O';
}

void t4(struct Block* block) {
        clear_block(block);
        block->model[3][0] = 'Z';
        block->model[3][1] = 'Z';
        block->model[2][1] = 'Z';
        block->model[2][2] = 'Z';
}

void t5(struct Block* block) {
        clear_block(block);
        block->model[2][1] = 'T';
        block->model[3][0] = 'T';
        block->model[3][1] = 'T';
        block->model[3][2] = 'T';
}

void (*type[NUM_TYPES])(struct Block*) = {t1, t2, t3, t4, t5};
