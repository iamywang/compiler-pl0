#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pl0.h"

void getch()
{
    if (ch_count == line_len)
    {
        if (feof(in))
        {
            "\nFINISHED!\n";
            return;
        }

        line_len = ch_count = 0;

        printf("%5d  ", code_pointer);

        while (1)
        {
            if (feof(in))
            {
                "\nFINISHED!\n";
                return;
            }
            ch = getc(in);
            if (ch == '\n')
                break;
            else
            {
                printf("%c", ch);
                line[++line_len] = ch;
            }
        }
        printf("\n");
        line[++line_len] = ' ';
    }
    // printf("ch_count: %d, line_len: %d, code_pointer: %d\n", ch_count, line_len, code_pointer);
    ch = line[++ch_count];
}

int getsym()
{
    int i, k;
    char a[MAX_ID_LENGTH + 1];

    while (ch == ' ')
        getch();

    if (isalpha(ch))
    {
        k = 0;
        do
        {
            if (k < MAX_ID_LENGTH)
                a[k++] = ch;
            getch();
        } while (isalpha(ch) || isdigit(ch));
        a[k] = 0;
        strcpy(id, a);
        word[0] = id;
        i = REVERSED_WORD_NUMBER;
        while (strcmp(id, word[i--]))
            ;
        if (++i)
            sym = word_sym[i];
        else
            sym = ID_SYM;
    }
    else if (isdigit(ch))
    {
        k = num = 0;
        sym = NUM_SYM;
        do
        {
            num = num * 10 + ch - '0';
            k++;
            getch();
        } while (isdigit(ch));
        if (k > MAX_NUMBER_LENGTH)
            printf("Warning(MAX_NUMBER_LENGTH): EXPECTED: %d, GOT: %d!\n", MAX_NUMBER_LENGTH, k);
    }
    else if (ch == ':')
    {
        getch();
        if (ch == '=')
        {
            sym = ASSIGNMENT_SYM; // :=
            getch();
        }
        else
        {
            sym = NULL_SYM;
            printf("Error(ILLEGAL_OPERATOR): ILLEGAL ASSIGNMENT OPERATOR: ':=', GOT: ':%s'!\n", ch);
        }
    }
    else if (ch == '>')
    {
        getch();
        if (ch == '=')
        {
            sym = BIGEQ_SYM; // >=
            getch();
        }
        else
        {
            sym = BIG_SYM; // >
        }
    }
    else if (ch == '<')
    {
        getch();
        if (ch == '=')
        {
            sym = LESSEQ_SYM; // <=
            getch();
        }
        else
        {
            sym = LESS_SYM; // <
        }
    }
    else
    {
        i = CHAR_SYMBOL_NUMBER;
        chars[0] = ch;
        while (chars[i--] != ch)
            ;
        if (++i)
        {
            sym = char_sym[i];
            getch();
        }
        else
            return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ch = ' ';
    ch_count = 0;
    line_len = 0;
    code_pointer = 0;

    in = fopen(argv[1], "r");
    int return_code = getsym();

    if (return_code == -1)
        printf("Error\n");

    return 0;
}