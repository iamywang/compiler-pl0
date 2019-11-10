#ifndef LEX_H
#define LEX_H

#include "base.h"

enum SYM_TYPE
{
    /*****************************/
    NULL_SYM, // 无保留
    NUM_SYM,  // number类别
    ID_SYM,   // 标识符类别
    /*****************************/
    CONST_SYM,     // const 常量
    VAR_SYM,       // var 变量
    PROCEDURE_SYM, // 过程
    /*****************************/
    BEGIN_SYM, // begin
    END_SYM,   // end
    OOD_SYM,   // ood 表达式
    IF_SYM,    // if
    THEN_SYM,  // then
    ELSE_SYM,  // else
    CALL_SYM,  // call
    WHILE_SYM, // while
    DO_SYM,    // do
    READ_SYM,  // read
    WRITE_SYM, // write
    /*****************************/
    PLUS_SYM,  // +
    MINUS_SYM, // -
    MUL_SYM,   // *
    DIV_SYM,   // /
    /*****************************/
    ASSIGNMENT_SYM, // :=
    EQUAL_SYM,      // =
    NOTEQ_SYM,      // #
    LESS_SYM,       // <
    LESSEQ_SYM,     // <=
    BIG_SYM,        // >
    BIGEQ_SYM,      // >=
    /*****************************/
    LEFTP_SYM,  // (
    RIGHTP_SYM, // )
    LEFTB_SYM,  // {
    RIGHTB_SYM, // }
    /*****************************/
    COMMA_SYM,     // ,
    SEMICOLON_SYM, // ;
    PERIOD_SYM,    // .
    /*****************************/
};

char *word[REVERSED_WORD_NUMBER + 1] = {"", "const", "var", "procedure", "begin", "end", "odd", "if", "then", "else", "call", "while", "do", "read", "write"};
int word_sym[REVERSED_WORD_NUMBER + 1] = {NULL_SYM, CONST_SYM, VAR_SYM, PROCEDURE_SYM, BEGIN_SYM, END_SYM, OOD_SYM, IF_SYM, THEN_SYM, ELSE_SYM, CALL_SYM, WHILE_SYM, DO_SYM, READ_SYM, WRITE_SYM};

char chars[CHAR_SYMBOL_NUMBER + 1] = {' ', '+', '-', '*', '/', '=', '#', '<', '>', '(', ')', '{', '}', ',', ';', '.'};
int char_sym[CHAR_SYMBOL_NUMBER + 1] = {NULL_SYM, PLUS_SYM, MINUS_SYM, MUL_SYM, DIV_SYM, EQUAL_SYM, NOTEQ_SYM, LESS_SYM, BIG_SYM, LEFTP_SYM, RIGHTP_SYM, LEFTB_SYM, RIGHTB_SYM, COMMA_SYM, SEMICOLON_SYM, PERIOD_SYM};

char lex_code[CXMAX]; // 存放代码
int code_pos = 0;     // 当前位置

char ch;                    // 读到的字符
enum SYM_TYPE sym;          // 关键字类型
char id[MAX_ID_LENGTH + 1]; // 标识符的值
int num;                    // 数字的值
int line = 1;               // 行数

void getch();
int getsym();

#endif
