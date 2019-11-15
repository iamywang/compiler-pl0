#ifndef PAESR_H
#define PARSE_H

#include "base.h"
#include "lex.h"

// 1. 说明部分的处理

typedef struct
{
    char name[MAX_ID_LENGTH + 1];
    int kind;
    int value;
} comtab;

typedef struct
{
    char name[MAX_ID_LENGTH + 1];
    int kind;
    short level;
    short address;
} mask;

comtab table[TXMAX]; // 表

int level = 0; // 当前层次
int tx = 0;    // table指针
int dx;        // 每层的局部量的相对地址

void enter(int kind);   // 添加到table中
int position(char *id); // 确定在table中的位置

// 2. 语句处理和代码生成

typedef struct
{
    int f; // 功能码
    int l; // 层差
    int a; // 位移量
} instruction;

enum ID_TYPE
{
    ID_CONST,
    ID_VAR,
    ID_PROCEDURE
};

enum INS_CODE
{
    LIT,
    OPR,
    LOD,
    STO,
    CAL,
    INT,
    JMP,
    JPC
};

enum OPR_CODE
{
    OPR_EXT, // exit
    OPR_ADD, // +
    OPR_MIN, // -
    OPR_MUL, // *
    OPR_DIV, // /
    OPR_EQU, // =
    OPR_NEQ, // #
    OPR_LES, // <
    OPR_LEQ, // <=
    OPR_GTR, // >
    OPR_GEQ  // >=
};

char *ins[MAX_INS] = {"LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"}; // 指令代码

int cx;                  // 当前要生成的代码编号
instruction code[CXMAX]; // 生成的指令

void gen(int f, int l, int a); //代码生成

// 3. 词法分析

void constdeclaration();
void vardeclaration();

void block();

#endif
