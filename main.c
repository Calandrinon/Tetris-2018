#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "block.h"

char screen[SCREEN_H][SCREEN_W];
struct Block blocks[256];
int num_blocks;

void init_screen() {
        for (int i = 0; i < SCREEN_H; i++) {
                for (int j = 0; j < SCREEN_W; j++)
                        screen[i][j] = ' ';
        }
}

void blit_screen() {
        for (int i = 0; i < SCREEN_H; i++) {
                for (int j = 0; j < SCREEN_W; j++)
                        printf("%c ", screen[i][j]);
                printf("\n");
        }
}

void draw_block_to_screen(struct Block *block) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                        if (block->model[i][j] != ' ') {
                                screen[i + block->x][j + block->y] = block->model[i][j];
                        }
                }
        }
}

void draw_blocks() {
        for (int i = 0; i < num_blocks; i++)
                draw_block_to_screen(&blocks[i]);
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
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                        if (block->model[i][j] != ' ')
                                screen[i + block->x][j + block->y] = ' ';
                }
        }
}

bool left_collision(struct Block *block) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j - 1] == ' ' && (screen[block->x + i][block->y + j - 1] != ' ' || block->y + j - 1 < 0))
                                return true;
                }
        }

        return false;
}

bool right_collision(struct Block *block) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j + 1] == ' ' && (screen[block->x + i][block->y + j + 1] != ' ' || block->y + j + 1 >= SCREEN_W))
                                return true;
                }
        }

        return false;
}

bool bottom_collision(struct Block *block) {
        for (int i = 0; i <= BLOCK_SIZE - 1; i++) {
                if (block->model[BLOCK_SIZE - 1][i] != ' ' && screen[block->x + BLOCK_SIZE][block->y + i] != ' ')
                        return true;
        }

        for (int i = BLOCK_SIZE - 2; i >= 0; i--) {
                for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
                        if (block->model[i][j] != ' ' && block->model[i + 1][j] == ' '
                         && screen[block->x + i + 1][block->y + j] != ' ')
                                return true;
                }
        }

        return false;
}

void input() {
        if (key_pressed(VK_LEFT) && !left_collision(&blocks[num_blocks - 1])) {
                blocks[num_blocks - 1].y--;
        }

        if (key_pressed(VK_RIGHT) && !right_collision(&blocks[num_blocks - 1])) {
                blocks[num_blocks - 1].y++;
        }

        if (key_pressed(VK_D)) {
                rotate_block(&blocks[num_blocks - 1]);
        }
}

void drop_block() {
        if (bottom_collision(&blocks[num_blocks - 1]) || blocks[num_blocks - 1].x + BLOCK_SIZE == SCREEN_H - 1) {
                add_block();
        }

        blocks[num_blocks - 1].x++;
}

int main() {
        init_screen();
        add_block();

        while (!key_pressed(VK_ESCAPE)) {
                clear_block_image(&blocks[num_blocks - 1]);
                input();
                drop_block();

                draw_blocks();
                blit_screen();

                Sleep(250);
                system("cls");
        }

        return 0;
}
