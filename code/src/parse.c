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
        mask *mk;
        if (!(i = position(id)))
            error(10);
        else if (table[i].kind != ID_VAR)
        {
            error(2);
            i = 0;
        }
        getsym();
        if (sym == ASSIGNMENT_SYM)
            getsym();
        else
            error(2);
        // 表达式
        expression(sym);
        mk = (mask *)&table[i];
        if (i)
            gen(STO, level - mk->level, mk->address);
        break;
    case BEGIN_SYM:
        getsym();
        set1 = initSet(SEMICOLON_SYM, END_SYM, NULL_SYM);
        set2 = unionSet(set1, symset);
        statement(set2);
        while (sym == SEMICOLON_SYM || inSet(sym, statementsym))
        {
            if (sym == SEMICOLON_SYM)
                getsym();
            else
                error(10);
            statement(set2);
        }
        if (sym == END_SYM)
            getsym();
        else
            error(8);
        break;
    case CALL_SYM:
        getsym();
        if (sym != ID_SYM)
            error(11);
        else
        {
            if (!(i = position(id)))
                error(10);
            else if (table[i].kind == ID_PROCEDURE)
            {
                mask *mk;
                mk = (mask *)&table[i];
                gen(CAL, level - mk->level, mk->address);
            }
            else
                error(17);
            getsym();
        }
        break;
    case WHILE_SYM:
        cx1 = cx;
        getsym();
        set1 = initSet(DO_SYM, NULL_SYM);
        set2 = unionSet(set1, symset);
        // 条件状态
        condition(set2);
        cx2 = cx;
        gen(JPC, 0, 0);
        if (sym == DO_SYM)
            getsym();
        else
            error(18);
        // 语句
        statement(symset);
        gen(JMP, 0, cx1);
        code[cx2].a = cx;
        break;
    case IF_SYM:
        getsym();
        set1 = initSet(THEN_SYM, DO_SYM, NULL_SYM);
        set2 = unionSet(set1, symset);
        // 条件
        condition(set2);
        if (sym == THEN_SYM)
            getsym();
        else
            error(19);
        cx1 = cx;
        gen(JPC, 0, 0);
        // 语句
        statement(symset);
        code[cx1].a = cx;
        break;
    case READ_SYM:
        break;
    case WRITE_SYM:
        break;
    }
    // test(symset, nullsym, 0);
}

void expression(set symset)
{
    int addop;
    set set1;

    set1 = unionSet(symset, initSet(PLUS_SYM, MINUS_SYM, NULL_SYM));
    if (sym == PLUS_SYM || sym == MINUS_SYM)
    {
        addop = sym;
        getsym();

        term(set1);
        if (addop == MINUS_SYM)
            gen(OPR, 0, OPR_NEG);
    }
    else
        term(set1);

    while (sym == PLUS_SYM || sym == MINUS_SYM)
    {
        addop = sym;
        getsym();

        term(set1);
        if (addop == PLUS_SYM)
            gen(OPR, 0, OPR_ADD);
        else
            gen(OPR, 0, OPR_MIN);
    }
}

void condition(set symset)
{
    int relop;
    set set1 = unionSet(relsym, symset);
    expression(set1);

    if (!inSet(sym, relsym))
        error(20);

    else // 关系符号
    {
        relop = sym;
        getsym();

        expression(symset);
        switch (relop)
        {
        case EQUAL_SYM:
            gen(OPR, 0, OPR_EQU);
            break;
        case NOTEQ_SYM:
            gen(OPR, 0, OPR_NEQ);
            break;
        case LESS_SYM:
            gen(OPR, 0, OPR_LES);
            break;
        case LESSEQ_SYM:
            gen(OPR, 0, OPR_LEQ);
            break;
        case BIG_SYM:
            gen(OPR, 0, OPR_GTR);
            break;
        case BIGEQ_SYM:
            gen(OPR, 0, OPR_GEQ);
            break;
        }
    }
}

void term(set symset)
{
    int mulop;
    set set1;

    set1 = unionSet(symset, initSet(MUL_SYM, DIV_SYM, NULL_SYM));
    factor(set1);
    while (sym == MUL_SYM || sym == DIV_SYM)
    {
        mulop = sym;
        getsym();

        factor(set1);
        if (mulop == MUL_SYM)
            gen(OPR, 0, OPR_MUL);
        else
            gen(OPR, 0, OPR_DIV);
    }
}

void factor(set symset)
{
    int i;
    set set1;

    // test(factorsym, symset, 0);

    while (inset(sym, factorsym))
    {
        if (sym == ID_SYM)
        {
            if ((i = position(id)) == 0)
                error(10);
            else
                switch (table[i].kind)
                {
                    mask *mk;
                case ID_CONST:
                    gen(LIT, 0, table[i].value);
                    break;
                case ID_VAR:
                    mk = (mask *)&table[i];
                    gen(LOD, level - mk->level, mk->address);
                    break;
                case ID_PROCEDURE:
                    error(21);
                    break;
                }
            getsym();
        }
        else if (sym == NUM_SYM)
        {
            if (num > MAX_ADDR)
            {
                error(1);
                num = 0;
            }
            gen(LIT, 0, num);
            getsym();
        }
        else if (sym == LEFTP_SYM)
        {
            getsym();
            set1 = unionSet(initSet(RIGHTP_SYM, NULL_SYM), symset);
            expression(set1);
            if (sym == RIGHTP_SYM)
                getsym();
            else
                error(22);
        }
        // test(symset, initSet(LEFTP_SYM, NULL_SYM), 0);
    }
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
                // test(nextset, symset, 0);
            }
            else
                error(8);
        }

        set nextset = unionSet(statementsym, initSet(ID_SYM, NULL_SYM));
        // test(nextset, declaresym, 0);
    } while (inSet(sym, declaresym));

    code[mk->address].a = cx;
    mk->address = cx;
    gen(INT, 0, block_dx);

    set nextset = unionSet(symset, initSet(SEMICOLON_SYM, END_SYM, NULL_SYM));
    statement(nextset);

    gen(OPR, 0, OPR_EXT); // OPR 0 0
    // test(symset, nullsym, 0);
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