/* 把关键字、算符、界符称为语言固有的单词，标识符、常量称为用户自定义的单词。为此设置三个全程量：SYM,ID,NUM 。
 SYM：存放每个单词的类别，为内部编码的表示形式。
 ID：存放用户所定义的标识符的值，即标识符字符串的机内表示。
 NUM：存放用户定义的数。
 GETSYM要完成的任务：
1.滤掉单词间的空格。
2.识别关键字，用查关键字表的方法识别。当单词是关键字时，将对应的类别放在SYM中。如IF的类别为IFSYM，THEN的类别为THENSYM。
3.识别标识符，标识符的类别为IDENT，IDENT放在SYM中，标识符本身的值放在ID中。关键字或标识符的最大长度是10。
4.拼数，将数的类别NUMBER放在SYM中，数本身的值放在NUM中。
5.拼由两个字符组成的运算符，如：>=、<=等等，识别后将类别存放在SYM中。
6.打印源程序，边读入字符边打印。
由于一个单词是由一个或多个字符组成的，所以在词法分析程序GETSYM中定义一个读字符过程GETCH。 */

#include <stdio.h>
#include <stdlib.h>

#define REVERSED_WORD_NUMBER 14 // 保留字个数
#define CHAR_SYMBOL_NUMBER 15   // 各种符号个数
#define MAX_SYM_LENGTH 10       // 关键字最大长度
#define MAX_ID_LENGTH 10        // 标识符最大长度
#define MAX_NUMBER_LENGTH 14    // 数字最大长度

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

char *err_msg[] = {
    "The length of ID is too long, expected less than 10.",            // 标识符长度过长
    "The length of NUM is too long, expected less than 10.",           // 数字长度过长
    "Iillegal ASSIGNMENT_SYM, expected ':='",                          // 非法赋值运算符
    "The length of code is too long, expected no more than 500 chars." // 代码总量过长
};

FILE *in; // 文件

char code[500];   // 存放代码
int code_pos = 0; // 当前位置

char ch;                    // 读到的字符
enum SYM_TYPE sym;          // 关键字类型
char id[MAX_ID_LENGTH + 1]; // 标识符的值
int num;                    // 数字的值
int line = 1;               // 行数

void getch();
int getsym();
void error(int error_code)
{
    printf("错误<error: %d, %s>\n", error_code, err_msg[error_code]);
}
