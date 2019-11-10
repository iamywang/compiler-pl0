#include "lex.c"
#include "parse.c"
#include "interpreter.c"

void lex_anal()
{
    // 词法分析
    for (int i = 0; i < 500; i++)
        lex_code[i] = '\0';

    while (getsym())
        ;
    for (int i = 0; i < code_pos; i++)
        printf("%c", lex_code[i]);
}

void syn_anal()
{
    // 语法分析
}

void exec()
{
    // 解释执行
    interpret();
}

int main(int argc, char *argv[])
{
    in = fopen(argv[1], "r"); // 读入文件
    lex_anal();
    syn_anal();
    exec();
    return 0;
}