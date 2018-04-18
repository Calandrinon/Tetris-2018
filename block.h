#ifndef BLOCK_H
#define BLOCK_H

struct Block {
        char model[4][4];
        int x, y;
};

void clear_block(struct Block*);
void t1(struct Block*);
void t2(struct Block*);
void t3(struct Block*);
void t4(struct Block*);
void t5(struct Block*);
void t6(struct Block*);
void t7(struct Block*);
void (*type[7])(struct Block*);

#endif
