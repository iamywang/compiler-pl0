#include "headers/parse.h"

void enter(int kind)
{
    mask *mk;
    tx++;
    strcpy(table[tx].name, id);
    table[tx].kind = kind;
    switch (kind)
    {
    case CONST_SYM:
        if (num > MAX_ADDR)
        {
            error(1); // The number is too great.
            num = 0;
        }
        table[tx].value = num;
        break;
    case VAR_SYM:
        mk = (mask *)&table[tx];
        mk->level = level;
        mk->address = dx++;
        break;
    case PROCEDURE_SYM:
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
        printf("Fatal Error: Program too long.\n");
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
                error(5); // Found ':=' when expecting '='.
            getsym();
            if (sym == NUM_SYM)
            {
                enter(CONST_SYM);
                getsym();
            }
            else
            {
                error(6); // There must be a number to follow '='.
            }
        }
        else
        {
            error(5); // There must be an '=' to follow the identifier.
        }
    }
    error(4); // There must be an identifier to follow 'const', 'var', or 'procedure'.
}

void vardeclaration()
{
    if (sym == ID_SYM)
    {
        enter(VAR_SYM);
        getsym();
    }
    else
    {
        error(4); // There must be an identifier to follow 'const', 'var', or 'procedure'.
    }
}