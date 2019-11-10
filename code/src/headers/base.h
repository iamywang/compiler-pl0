#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REVERSED_WORD_NUMBER 14 // 保留字个数
#define CHAR_SYMBOL_NUMBER 15   // 各种符号个数
#define MAX_SYM_LENGTH 10       // 关键字最大长度
#define MAX_ID_LENGTH 10        // 标识符最大长度
#define MAX_NUMBER_LENGTH 14    // 数字最大长度

#define LEVEL 3        //最大层数
#define MAX_SYM_NUM 50 // 最多允许符号数
#define MAX_INS 8      // 目标指令数量
#define MAX_ADDR 65535 // 最大地址空间
#define CXMAX 500
#define TXMAX 500

#define STACK_SIZE 1024

FILE *in; // 文件

#ifndef ERROR_ANAL
#define ERROR_ANAL

char *err_msg[] = {
    "The length of ID is too long, expected less than 10.",                 // 标识符长度过长
    "The length of NUM is too long, expected less than 10.",                // 数字长度过长
    "Iillegal ASSIGNMENT_SYM, expected ':='",                               // 非法赋值运算符
    "The length of code is too long, expected no more than 500 chars."      // 代码总量过长
    "There must be an identifier to follow 'const', 'var', or 'procedure'." // 缺少标识符
    "There must be a '=' to follow identifier."                             // 常量声明应该是 =
    "There must be a number to follow '='."                                 // = 后面缺少数字
};

void error(int error_code)
{
    printf("错误<error: %d, %s>\n", error_code, err_msg[error_code]);
}

#endif