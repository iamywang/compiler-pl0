#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#define REVERSED_WORD_NUMBER 14 // 保留字个数
#define CHAR_SYMBOL_NUMBER 13   // 各种符号个数
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

FILE *in;          // 文件
int line = 1;      // 行数
int error_num = 0; // 错误数

// 定义集合操作，用于递归语法分析
typedef struct set_item
{
    int item;
    struct set_item *next; // next
} set_item, *set;

void insertSet(set s, int item) // 向集合中添加元素
{
    set_item *p = s;
    set_item *q;

    while (p->next && p->next->item < item)
    {
        p = p->next;
    }

    q = (set_item *)malloc(sizeof(set_item));
    q->item = item;
    q->next = p->next;
    p->next = q;
}

set initSet(int item, ...) // 初始化集合
{
    va_list list;
    set s;

    s = (set_item *)malloc(sizeof(set_item));
    s->next = NULL;

    va_start(list, item);
    while (item)
    {
        insertSet(s, item);
        item = va_arg(list, int);
    }
    va_end(list);
    return s;
}

set unionSet(set s1, set s2) // 合并两个集合
{
    set s;
    set_item *p;

    s = p = (set_item *)malloc(sizeof(set_item));
    while (s1 && s2)
    {
        p->next = (set_item *)malloc(sizeof(set_item));
        p = p->next;
        if (s1->item < s2->item)
        {
            p->item = s1->item;
            s1 = s1->next;
        }
        else
        {
            p->item = s2->item;
            s2 = s2->next;
        }
    }

    while (s1)
    {
        p->next = (set_item *)malloc(sizeof(set_item));
        p = p->next;
        p->item = s1->item;
        s1 = s1->next;
    }

    while (s2)
    {
        p->next = (set_item *)malloc(sizeof(set_item));
        p = p->next;
        p->item = s2->item;
        s2 = s2->next;
    }

    p->next = NULL;

    return s;
}

int inSet(int item, set s) // 判断是否在集合内
{
    s = s->next;
    while (s && s->item < item)
        s = s->next;
    if (s && s->item == item)
        return 1;
    else
        return 0;
}

char *err_msg[] = {
    "The length of ID is too long, expected less than 10.",                  // 标识符长度过长
    "The length of NUM is too long, expected less than 10.",                 // 数字长度过长
    "Iillegal ASSIGNMENT_SYM, expected ':='",                                // 非法赋值运算符
    "The length of code is too long, expected no more than 500 chars.",      // 代码总量过长
    "There must be an identifier to follow 'const', 'var', or 'procedure'.", // 缺少标识符
    "There must be a '=' to follow identifier.",                             // 常量声明应该是 =
    "There must be a number to follow '='.",                                 // = 后面缺少数字
    "There are too many levels.",                                            // level 太多
    "There may miss a ',' or ';'.",                                          // 缺少, ;
    "The Identifier is illegal.",                                            // 非法标识符
    "You must declare the identifier before use it.",                        // 未声明标识符
    "There should be an identifier to follow 'call'.",                       // call 后跟标识符
    "There should be an identifier to follow 'begin'.",                      // begin 后跟标识符
    "There should be an identifier to follow 'while'.",                      // while 后跟标识符
    "There should be an identifier to follow 'if'.",                         // if 后跟标识符
    "There should be an identifier to follow 'read'.",                       // read 后跟标识符
    "There should be an identifier to follow 'write'.",                      // write 后跟标识符
    "You can only call procedure.",                                          // 被call调用的必须是procedure
    "There must be 'do'.",                                                   // do
    "There must be 'then'.",                                                 // then
    "The operator is illegal expected: '= # > < >= <='.",                    // 符号不在关系运算符中
    "Procedure identifier can not be in an expression.",                     //
    "There may miss a ')'.",                                                 // 缺少右括号
    "There should be a '.' at the end of PL/0 program.",                     // 必须以.结尾
    "There should be a '(' to follow 'write'.",                              // write后必须跟(
    "There should be a ')' to follow identifier.",                           // 标识符后面（read write）必须要有)
    "It is illegal when divided by zero.",                                   // 除法运算时0不能做除数
};

void error(int error_code)
{
    error_num++;
    printf("错误 <line: %d, error: %d, %s>\n", line, error_code, err_msg[error_code]);
}

#endif
