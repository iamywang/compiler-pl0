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