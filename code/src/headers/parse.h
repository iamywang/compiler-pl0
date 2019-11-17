#ifndef PARSE_H
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
    OPR_GEQ, // >=
    OPR_NEG, // 取反
    OPR_RED, // 读入
    OPR_WRT, // 将栈顶内容输出到标准输出
};

char *ins[MAX_INS] = {"LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"}; // 指令代码

int cx;                  // 当前要生成的代码编号
instruction code[CXMAX]; // 生成的指令

void gen(int f, int l, int a); //代码生成

// 3. 词法分析

set nullsym, relsym, declaresym, statementsym, factorsym;

void constdeclaration();
void vardeclaration();

void statement(set symset);  // 语句处理
void expression(set symset); // 表达式处理+-*/
void condition(set symset);  // 状态
void term(set symset);       // 项
void factor(set symset);     // 因子

void read(char *id);  // 从标准输入读变量
void write(char *id); // 写变量到标准输出

void block(set symset);

#endif
