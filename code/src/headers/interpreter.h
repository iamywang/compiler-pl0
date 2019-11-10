#include "base.h"
#include "parse.h"

int stack[STACK_SIZE]; // stack

instruction i; // 指令寄存器
int pc;        // 程序地址寄存器
int t;         // 栈顶寄存器
int b;         // 基地址寄存器

void interpret();
