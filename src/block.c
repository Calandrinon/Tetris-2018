#include <stdio.h>
#include "block.h"

void clear_block(struct Block* block) {
        for (int i = 0; i < MAX_BLOCK_SIZE; i++) {
                for (int j = 0; j < MAX_BLOCK_SIZE; j++)
                        block->model[i][j] = ' ';
        }
}

void t1(struct Block* block) {
        clear_block(block);
        block->size = 4;
        block->model[3][0] = 'I';
        block->model[3][1] = 'I';
        block->model[3][2] = 'I';
        block->model[3][3] = 'I';
}

void t2(struct Block* block) {
        clear_block(block);
        block->size = 3;
        block->model[1][0] = 'L';
        block->model[2][0] = 'L';
        block->model[2][1] = 'L';
        block->model[2][2] = 'L';
}

void t3(struct Block* block) {
        clear_block(block);
        block->size = 2;
        block->model[0][0] = 'O';
        block->model[0][1] = 'O';
        block->model[1][0] = 'O';
        block->model[1][1] = 'O';
}

void t4(struct Block* block) {
        clear_block(block);
        block->size = 3;
        block->model[2][0] = 'Z';
        block->model[2][1] = 'Z';
        block->model[1][1] = 'Z';
        block->model[1][2] = 'Z';
}

void t5(struct Block* block) {
        clear_block(block);
        block->size = 3;
        block->model[1][1] = 'T';
        block->model[2][0] = 'T';
        block->model[2][1] = 'T';
        block->model[2][2] = 'T';
}

void (*type[NUM_TYPES])(struct Block*) = {t1, t2, t3, t4, t5};

struct Block generate_block() {
        struct Block block;

        srand(time(NULL));
        block.type = rand() % NUM_TYPES;
        type[block.type](&block);
        block.x = -block.size - 1;
        block.y = SCREEN_W / 2 - 1;

        return block;
}

void rotate_block(struct Block *block) {
        char new_model[MAX_BLOCK_SIZE][MAX_BLOCK_SIZE];

        for (int i = block->size - 1; i >= 0; i--) {
                for (int j = block->size - 1; j >= 0; j--) {
                        new_model[block->size - j - 1][i] = block->model[i][j];

                        if (screen[block->x + block->size - j - 1][block->y + i] != ' ')
                                return;
                }
        }

        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        block->model[i][j] = new_model[i][j];
                }
        }

        if (block->y < 0) {
                block->y = 0;
        } else if (block->y > SCREEN_W - block->size) {
                block->y = SCREEN_W - block->size;
        }
}
