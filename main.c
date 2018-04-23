#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "block.h"

char screen[SCREEN_H][SCREEN_W];
struct Block cr_block;
int num_blocks, sleep_time = 333;

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
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ') {
                                screen[i + block->x][j + block->y] = block->model[i][j];
                        }
                }
        }
}

void create_block() {
        cr_block = generate_block();
}

bool key_pressed(int key) {
        return (GetAsyncKeyState(key) & 0x8000);
}

void clear_block_image(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ')
                                screen[i + block->x][j + block->y] = ' ';
                }
        }
}

bool left_collision(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j - 1] == ' ' && (screen[block->x + i][block->y + j - 1] != ' ' || block->y + j - 1 < 0))
                                return true;
                }
        }

        return false;
}

bool right_collision(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j + 1] == ' ' && (screen[block->x + i][block->y + j + 1] != ' ' || block->y + j + 1 >= SCREEN_W))
                                return true;
                }
        }

        return false;
}

bool bottom_collision(struct Block *block) {
        for (int i = 0; i <= block->size - 1; i++) {
                if (block->model[block->size - 1][i] != ' ' && screen[block->x + block->size][block->y + i] != ' ')
                        return true;
        }

        for (int i = block->size - 2; i >= 0; i--) {
                for (int j = block->size - 1; j >= 0; j--) {
                        if (block->model[i][j] != ' ' && block->model[i + 1][j] == ' '
                         && screen[block->x + i + 1][block->y + j] != ' ')
                                return true;
                }
        }

        return false;
}

void input() {
        if (key_pressed(VK_LEFT) && !left_collision(&cr_block)) {
                cr_block.y--;
        }

        if (key_pressed(VK_RIGHT) && !right_collision(&cr_block)) {
                cr_block.y++;
        }

        if (key_pressed(VK_DOWN)) {
                sleep_time = 5;
        } else {
                sleep_time = 333;
        }

        if (key_pressed(VK_D)) {
                rotate_block(&cr_block);
        }
}

void drop_block() {
        if (bottom_collision(&cr_block) || cr_block.x + cr_block.size == SCREEN_H) {
                create_block();
        }

        cr_block.x++;
}

void delete_lines() {
        bool line_del = false;
        for (int i = SCREEN_H - 1; i >= 0; i--) {
                bool full = true;
                for (int j = SCREEN_W - 1; j >= 0; j--) {
                        if (screen[i][j] == ' ') {
                                full = false;
                                break;
                        }
                }

                if (full) {
                        line_del = true;
                        for (int j = SCREEN_W - 1; j >= 0; j--) {
                                screen[i][j] = ' ';
                        }
                }
        }

        if (!line_del)
                return;

        for (int i = SCREEN_H - 1; i >= 0; i--) {
                for (int j = SCREEN_W - 1; j >= 0; j--) {
                        if (screen[i][j] != ' ') {
                                int r = i + 1;
                                while(screen[r][j] == ' ' && r < SCREEN_H)
                                        r++;
                                screen[r - 1][j] = screen[i][j];
                                screen[i][j] = ' ';
                        }
                }
        }
}

int main() {
        init_screen();
        create_block();

        while (!key_pressed(VK_ESCAPE)) {
                if (!bottom_collision(&cr_block) && cr_block.x + cr_block.size != SCREEN_H)
                        clear_block_image(&cr_block);
                input();
                drop_block();
                delete_lines();

                draw_block_to_screen(&cr_block);
                blit_screen();

                Sleep(sleep_time);
                system("cls");
        }

        return 0;
}
