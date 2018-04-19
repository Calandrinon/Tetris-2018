#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "block.h"
#define SCREEN_W 10 //columns
#define SCREEN_H 14 //rows

char screen[SCREEN_H][SCREEN_W];
struct Block blocks[256];
int num_blocks;

void blit_screen() {
        for (int i = 0; i < SCREEN_H; i++) {
                for (int j = 0; j < SCREEN_W; j++)
                        printf("%c ", screen[i][j]);
                printf("\n");
        }
}

void draw_block_to_screen(struct Block *block) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++)
                        screen[i + block->x][j + block->y] = block->model[i][j];
        }
}

void draw_blocks() {
        for (int i = 0; i < num_blocks; i++)
                draw_block_to_screen(&blocks[i]);
}

struct Block generate_block() {
        struct Block block;

        srand(time(NULL));
        type[rand() % NUM_TYPES](&block);
        block.x = -BLOCK_SIZE - 1;
        block.y = rand() % (NUM_TYPES - 1);

        return block;
}

void add_block() {
        struct Block block = generate_block();
        blocks[num_blocks] = block;
        num_blocks++;
}

int main() {
        /*    TEST:
        add_block();

        while (blocks[0].x < SCREEN_H - BLOCK_SIZE) {
                blocks[0].x++;
                Sleep(500);
                system("cls");
                draw_blocks();
                blit_screen();
        }
        */
        return 0;
}
