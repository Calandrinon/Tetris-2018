#include <stdio.h>
#include <stdlib.h>
#include "block.h"

char screen[14][10];
struct Block blocks[256];
int num_blocks;

void blit_screen() {
        for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 10; j++)
                        printf("%c ", screen[i][j]);
                printf("\n");
        }
}

void draw_block_to_screen(struct Block *block) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++)
                        screen[i + block->x][j + block->y] = block->model[i][j];
        }
}

void draw_blocks() {
        for (int i = 0; i < num_blocks; i++)
                draw_block_to_screen(&blocks[i]);
}

/*
struct Block generate_block() {
        struct Block block;

        srand(time(NULL));
        type[rand() % 7](&block);
        block.x = rand() % 10;
        block.y = 0;

        return block;
}
*/

int main() {


        return 0;
}
