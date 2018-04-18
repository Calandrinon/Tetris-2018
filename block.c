#include <stdio.h>
#include "block.h"

void clear_block(struct Block* block) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++)
                        block->model[i][j] = ' ';
        }
}

void t1(struct Block* block) {
        clear_block(block);
        block->model[3][0] = '0';
        block->model[3][1] = '0';
        block->model[3][2] = '0';
        block->model[3][3] = '0';
}

void t2(struct Block* block) {
        clear_block(block);
        block->model[2][0] = '0';
        block->model[3][0] = '0';
        block->model[3][1] = '0';
        block->model[3][2] = '0';
}

void t3(struct Block* block) {
        clear_block(block);
        block->model[2][2] = '0';
        block->model[3][0] = '0';
        block->model[3][1] = '0';
        block->model[3][2] = '0';
}

void t4(struct Block* block) {
        clear_block(block);
        block->model[2][0] = '0';
        block->model[2][1] = '0';
        block->model[3][0] = '0';
        block->model[3][1] = '0';
}

void t5(struct Block* block) {
        clear_block(block);
        block->model[3][0] = '0';
        block->model[3][1] = '0';
        block->model[2][1] = '0';
        block->model[2][2] = '0';
}

void t6(struct Block* block) {
        clear_block(block);
        block->model[2][1] = '0';
        block->model[3][0] = '0';
        block->model[3][1] = '0';
        block->model[3][2] = '0';
}

void t7(struct Block* block) {
        clear_block(block);
        block->model[2][0] = '0';
        block->model[2][1] = '0';
        block->model[3][1] = '0';
        block->model[3][2] = '0';
}

void (*type[7])(struct Block*) = {t1, t2, t3, t4, t5, t6, t7};
