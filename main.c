#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include "block.h"
#define SCREEN_W 18 //columns
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

bool key_pressed(int key) {
        return (GetAsyncKeyState(key) & 0x8000);
}

void clear_block_image(struct Block *block) {
        for (int i = block->x; i <= block->x + BLOCK_SIZE; i++) {
                for (int j = block->y; j <= block->y + BLOCK_SIZE; j++)
                        screen[i][j] = ' ';
        }
}

void input() {
        if (key_pressed(VK_LEFT) && blocks[num_blocks - 1].y > 0) {
                blocks[num_blocks - 1].y--;
        }

        if (key_pressed(VK_RIGHT) && blocks[num_blocks - 1].y + BLOCK_SIZE < SCREEN_W) {
                blocks[num_blocks - 1].y++;
        }
}

void drop_block() {
        if (blocks[num_blocks - 1].x + BLOCK_SIZE == SCREEN_H - 1) {
                add_block();
        }

        blocks[num_blocks - 1].x++;
}

int main() {
        add_block();

        while (!key_pressed(VK_ESCAPE)) {
                clear_block_image(&blocks[num_blocks - 1]);
                input();
                drop_block();

                draw_blocks();
                blit_screen();

                Sleep(500);
                system("cls");
        }

        return 0;
}
