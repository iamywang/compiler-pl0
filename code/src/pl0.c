#include "parse.c"
#include "interpreter.c"

int main(int argc, char *argv[])
{
    in = fopen(argv[1], "r"); // 读入文件

    for (int i = 0; i < 500; i++)
        lex_code[i] = '\0';

    nullsym = initSet(NULL_SYM);
    relsym = initSet(EQUAL_SYM, NOTEQ_SYM, LESS_SYM, LESSEQ_SYM, BIG_SYM, BIGEQ_SYM, NULL_SYM);    // 关系
    declaresym = initSet(CONST_SYM, VAR_SYM, PROCEDURE_SYM, NULL_SYM);                             // 声明
    statementsym = initSet(BEGIN_SYM, CALL_SYM, IF_SYM, WHILE_SYM, READ_SYM, WRITE_SYM, NULL_SYM); // 表达式
    factorsym = initSet(ID_SYM, NUM_SYM, LEFTP_SYM, NULL_SYM);                                     // 项
    set symset = unionSet(unionSet(declaresym, statementsym), initSet(PERIOD_SYM, NULL_SYM));

    printf("词法分析结果：\n");
    getsym(); // 获取符号

    block(symset);

    if (sym != PERIOD_SYM)
        error(23);

    // 打印源代码
    printf("程序源代码：\n");
    for (int i = 0; i < code_pos; i++)
        printf("%c", lex_code[i]);
    printf("\n");

    //  打印目标代码
    printf("生成目标代码：\n");
    for (int i = 0; i < cx; i++)
        printf("%s %d %d\n", ins[code[i].f], code[i].l, code[i].a);

    // 解释执行
    printf("解释执行结果：\n");
    interpret();

    return 0;
}