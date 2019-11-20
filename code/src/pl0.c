#include "parse.c"
#include "interpreter.c"

int main(int argc, char *argv[])
{
    in = fopen(argv[1], "r"); // 读入文件

    for (int i = 0; i < CXMAX; i++)
        lex_code[i] = '\0';

    for (int i = 0; i < CXMAX; i++)
    {
        code[i].f = 0;
        code[i].l = 0;
        code[i].a = 0;
    }

    nullsym = initSet(NULL_SYM);
    relsym = initSet(EQUAL_SYM, NOTEQ_SYM, LESS_SYM, LESSEQ_SYM, BIG_SYM, BIGEQ_SYM, NULL_SYM);    // 关系
    declaresym = initSet(CONST_SYM, VAR_SYM, PROCEDURE_SYM, NULL_SYM);                             // 声明
    statementsym = initSet(BEGIN_SYM, CALL_SYM, IF_SYM, WHILE_SYM, READ_SYM, WRITE_SYM, NULL_SYM); // 表达式
    factorsym = initSet(ID_SYM, NUM_SYM, LEFTP_SYM, NULL_SYM);                                     // 项
    set symset = unionSet(unionSet(declaresym, statementsym), initSet(PERIOD_SYM, NULL_SYM));

    printf("\033[37m词法分析结果：\n\033[0m");
    getsym(); // 获取符号

    block(symset);

    getsym();
    if (sym != PERIOD_SYM)
        error(23);

    // 打印源代码
    printf("\033[37m程序源代码：\n\033[0m");
    for (int i = 0; i < code_pos; i++)
        printf("%c", lex_code[i]);
    printf("\n");

    //table
    // printf("\033[37m生成table：\n\033[0m");
    // for (int i = 0; i < tx; i++)
    //     printf("%s %d %d\n", table[i].name, table[i].kind, table[i].value);

    //  打印目标代码
    printf("\033[37m生成目标代码：\n\033[0m");
    for (int i = 0; i < cx; i++)
        printf("%s %d %d\n", ins[code[i].f], code[i].l, code[i].a);

    // 解释执行
    printf("\033[37m解释执行结果：\n\033[0m");
    interpret();

    printf("\033[33mProgram Execute successful, %d errors, exit code = %d.\n\033[0m", error_num, 0);

    return 0;
}