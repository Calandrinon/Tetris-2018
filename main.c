#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "block.h"

static struct Block cr_block;
static int num_blocks, sleep_time = 333, lines_removed, score = -20;

static void init_screen() {
        for (int i = 0; i < SCREEN_H; i++) {
                for (int j = 0; j < SCREEN_W; j++)
                        screen[i][j] = ' ';
        }
}

static void blit_screen() {
        system("cls");

        for (int i = 0; i <= SCREEN_W + 1; i++)
                printf("__");

        printf("\n");

        for (int i = 0; i < SCREEN_H; i++) {
                printf("| ");
                for (int j = 0; j < SCREEN_W; j++)
                        printf("%c ", screen[i][j]);
                printf("|\n");
        }

        for (int i = 0; i <= SCREEN_W + 1; i++)
                printf("__");

        printf("\n");
}

static void draw_block_to_screen(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ') {
                                screen[i + block->x][j + block->y] = block->model[i][j];
                        }
                }
        }
}

static void create_block() {
        cr_block = generate_block();
}

static bool key_pressed(int key) {
        return (GetAsyncKeyState(key) & 0x8000);
}

static void clear_block_image(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ')
                                screen[i + block->x][j + block->y] = ' ';
                }
        }
}

static bool left_collision(struct Block *block) {
        for (int i = 1; i < block->size; i++) {
                for (int j = 1; j < block->size; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j - 1] == ' '
                        && (screen[block->x + i][block->y + j - 1] != ' ' || block->y + j - 1 < 0))
                                return true;
                }
        }

        for (int i = 0; i < block->size; i++) {
                if (block->model[i][0] != ' ' && (screen[block->x + i][block->y - 1] != ' ' || block->y - 1 < 0)) {
                        return true;
                }
        }

        return false;
}

static bool right_collision(struct Block *block) {
        for (int i = 0; i < block->size; i++) {
                for (int j = 0; j < block->size; j++) {
                        if (block->model[i][j] != ' ' && block->model[i][j + 1] == ' ' && (screen[block->x + i][block->y + j + 1] != ' ' || block->y + j + 1 >= SCREEN_W))
                                return true;
                }
        }

        return false;
}

static bool bottom_collision(struct Block *block) {
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

static void input() {
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

static void drop_block() {
        if (bottom_collision(&cr_block) || cr_block.x + cr_block.size == SCREEN_H) {
                create_block();
                score += 10 * (lines_removed / 10 + 2);
        }

        cr_block.x++;
}

static void delete_lines() {
        bool line_del = false;
        int num_lines = 0;

        for (int i = SCREEN_H - 1; i >= 0; i--) {
                bool full = true;
                for (int j = SCREEN_W - 1; j >= 0; j--) {
                        if (screen[i][j] == ' ') {
                                full = false;
                                break;
                        }
                }

                if (full) {
                        num_lines++;
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

        if (!num_lines)
                return;

        lines_removed += num_lines;
        int line_score;

        switch (num_lines) {
                case 1:
                        line_score = 50;
                        break;
                case 2:
                        line_score = 150;
                        break;
                case 3:
                        line_score = 350;
                        break;
                case 4:
                        line_score = 1000;
                        break;
        }

        score += line_score * (lines_removed / 10 + 1);
}

static void display_score() {
        printf("\nSCORE: %d              LEVEL %d", score, lines_removed / 10 + 1);
}

int main() {
        init_screen();
        create_block();

        while (!key_pressed(VK_ESCAPE)) {
                if (!bottom_collision(&cr_block) && cr_block.x + cr_block.size != SCREEN_H)
                        clear_block_image(&cr_block);

                drop_block();
                input();
                delete_lines();

                draw_block_to_screen(&cr_block);
                blit_screen();

                display_score();
                Sleep(sleep_time);
        }

        return 0;
}
