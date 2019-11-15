#include "headers/parse.h"

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

void block()
{
    mask *mk;

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
            // unfinished
        }
    } while (1);
}