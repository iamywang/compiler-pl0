#include "headers/parse.h"
#include "lex.c"

void enter(int kind)
{
    mask *mk;
    tx++;
    strcpy(table[tx].name, id);
    table[tx].kind = kind;
    switch (kind)
    {
    case ID_CONST:
        if (num > MAX_ADDR)
        {
            error(1);
            num = 0;
        }
        table[tx].value = num;
        break;
    case ID_VAR:
        mk = (mask *)&table[tx];
        mk->level = level;
        mk->address = dx++;
        break;
    case ID_PROCEDURE:
        mk = (mask *)&table[tx];
        mk->level = level;
        break;
    }
}

int position(char *id)
{
    int i;
    strcpy(table[0].name, id);
    i = tx + 1;
    while (strcmp(table[--i].name, id) != 0)
        ;
    return i;
}

void gen(int f, int l, int a)
{
    if (cx > CXMAX)
    {
        printf("Error: Code too long.\n");
        exit(1);
    }
    code[cx].f = f;
    code[cx].l = l;
    code[cx++].a = a;
}

void constdeclaration()
{
    if (sym == ID_SYM)
    {
        getsym();
        if (sym == EQUAL_SYM || sym == ASSIGNMENT_SYM)
        {
            if (sym == ASSIGNMENT_SYM)
                error(5);
            getsym();
            if (sym == NUM_SYM)
            {
                enter(ID_CONST);
                getsym();
            }
            else
                error(6);
        }
        else
            error(5);
    }
    else
        error(4);
}

void vardeclaration()
{
    if (sym == ID_SYM)
    {
        enter(ID_VAR);
        getsym();
    }
    else
        error(4);
}

void statement(set symset)
{
    int i, cx1, cx2;
    set set1, set2;

    switch (sym)
    {
    case ID_SYM:
        break;
    case BEGIN_SYM:
        break;
    case CALL_SYM:
        break;
    case WHILE_SYM:
        break;
    case IF_SYM:
        break;
    case READ_SYM:
        break;
    case WRITE_SYM:
        break;
    default:
        break;
    }
    // test(symset, nullsym, 19);
}

void block(set symset)
{
    mask *mk;
    int savedTx;

    dx = 3;
    int block_dx = dx;
    mk = (mask *)&table[tx];
    mk->address = cx;
    gen(JMP, 0, 0);

    if (level > LEVEL)
        error(7); // 层数太多
    do
    {
        if (sym == CONST_SYM)
        {
            getsym();
            do
            {
                constdeclaration();
                while (sym == COMMA_SYM)
                {
                    getsym();
                    constdeclaration();
                }
                if (sym == SEMICOLON_SYM)
                    getsym();
                else
                    error(8); // Missing ',' or ';'.
            } while (sym == ID_SYM);
        }

        if (sym == VAR_SYM)
        {
            getsym();
            do
            {
                vardeclaration();
                while (sym == COMMA_SYM)
                {
                    getsym();
                    vardeclaration();
                }
                if (sym == SEMICOLON_SYM)
                    getsym();
                else
                    error(8);
            } while (sym == ID_SYM);
        }

        while (sym == PROCEDURE_SYM)
        {
            getsym();
            if (sym == ID_SYM)
            {
                enter(ID_PROCEDURE);
                getsym();
            }
            else
                error(4);

            if (sym == SEMICOLON_SYM)
                getsym();
            else
                error(8);
            level++;
            savedTx = tx;

            set nextset = unionSet(symset, initSet(SEMICOLON_SYM, NULL_SYM));
            block(nextset); // 递归
            tx = savedTx;
            level--;

            if (sym == SEMICOLON_SYM)
            {
                getsym();
                nextset = unionSet(statementsym, initSet(ID_SYM, PROCEDURE_SYM, NULL_SYM));
                // test(nextset, symset, 6);
            }
            else
                error(8);
        }

        set nextset = unionSet(statementsym, initSet(ID_SYM, NULL_SYM));
        // test(nextset, declaresym, 7);
    } while (inSet(sym, declaresym));

    code[mk->address].a = cx;
    mk->address = cx;
    gen(INT, 0, block_dx);

    set nextset = unionSet(symset, initSet(SEMICOLON_SYM, END_SYM, NULL_SYM));
    statement(nextset);

    gen(OPR, 0, OPR_EXT); // OPR 0 0
    // test(symset, nullsym, 8);
}

int main(int argc, char *argv[])
{
    in = fopen(argv[1], "r"); // 读入文件

    nullsym = initSet(NULL_SYM);
    relsym = initSet(EQUAL_SYM, NOTEQ_SYM, LESS_SYM, LESSEQ_SYM, BIG_SYM, BIGEQ_SYM, NULL_SYM);    // 关系
    declaresym = initSet(CONST_SYM, VAR_SYM, PROCEDURE_SYM, NULL_SYM);                             // 声明
    statementsym = initSet(BEGIN_SYM, CALL_SYM, IF_SYM, WHILE_SYM, READ_SYM, WRITE_SYM, NULL_SYM); // 表达式
    factorsym = initSet(ID_SYM, NUM_SYM, LEFTP_SYM, NULL_SYM);                                     // 项

    getsym(); // 获取符号

    set symset = unionSet(unionSet(declaresym, statementsym), initSet(PERIOD_SYM, NULL_SYM));
    block(symset);

    //  打印目标代码
    for (int i = 0; i < cx; i++)
        printf("%s %d %d\n", ins[code[i].f], code[i].l, code[i].a);
    return 0;
}