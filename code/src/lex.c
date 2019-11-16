#include "headers/lex.h"

void getch()
{
    ch = fgetc(in);
    lex_code[++code_pos] = ch;

    while (ch == '\n')
    {
        line++;
        getch();
    }
    if (ch == EOF)
        return;
}

int getsym()
{
    char token[MAX_ID_LENGTH + 1];

    for (int i = 0; i <= MAX_ID_LENGTH; i++)
        token[i] = '\0';

    getch();

    while (ch == ' ' || ch == '\t')
        getch();

    if (ch == EOF) // FINISH
        return 0;

    if (isalpha(ch)) // 字母，保留字或者标识符
    {
        int k = 0;
        do
        {
            token[k++] = ch;
            getch();
        } while (isalpha(ch) || isdigit(ch));

        fseek(in, -1, 1); //将当前光标位置左移一位
        code_pos--;

        if (k > MAX_ID_LENGTH)
            error(0);

        strcpy(id, token);
        // 判断是否保留字
        word[0] = id;
        int i = REVERSED_WORD_NUMBER;
        while (strcmp(id, word[i--]))
            ;
        if (++i)
        {
            sym = word_sym[i]; // 保留字
            printf("保留字 <line %d, '%s'>\n", line, word[i]);
        }
        else
        {
            sym = ID_SYM; // 标识符
            printf("标识符 <line %d, '%s'>\n", line, id);
        }
    }
    else if (isdigit(ch)) // 数字
    {
        int k = num = 0;
        sym = NUM_SYM;
        do
        {
            num = num * 10 + ch - '0';
            k++;
            getch();
        } while (isdigit(ch));

        fseek(in, -1, 1); //将当前光标位置左移一位
        code_pos--;

        printf("数字 <line %d, %d>\n", line, num);

        if (k > MAX_NUMBER_LENGTH)
            error(1);
    }

    else if (ch == ':')
    {
        getch();
        if (ch == '=')
        {
            sym = ASSIGNMENT_SYM;
            printf("运算符 <line %d, ':='>\n", line);
        }
        else
            error(2);
    }
    else if (ch == '<')
    {
        getch();
        if (ch == '=')
        {
            sym = LESSEQ_SYM;
            printf("运算符 <line %d, '<='>\n", line);
        }
        else
        {
            sym = LESS_SYM;
            printf("运算符 <line %d, '<'>\n", line);
        }
    }
    else if (ch == '>')
    {
        getch();
        if (ch == '=')
        {
            sym = BIGEQ_SYM;
            printf("运算符 <line %d, '>='>\n", line);
        }
        else
        {
            sym = BIG_SYM;
            printf("运算符 <line %d, '>'>\n", line);
        }
    }
    else if (ch == '=')
    {
        sym = EQUAL_SYM;
        printf("运算符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == '#')
    {
        sym = NOTEQ_SYM;
        printf("运算符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == '+')
    {
        sym = PLUS_SYM;
        printf("运算符<line %d, '%c'>\n", line, ch);
    }
    else if (ch == '-')
    {
        sym = MINUS_SYM;
        printf("运算符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == '*')
    {
        sym = MUL_SYM;
        printf("运算符<line %d, '%c'>\n", line, ch);
    }
    else if (ch == '/')
    {
        sym = DIV_SYM;
        printf("运算符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == '(')
    {
        sym = LEFTP_SYM;
        printf("界符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == ')')
    {
        sym = RIGHTP_SYM;
        printf("界符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == ',')
    {
        sym = COMMA_SYM;
        printf("界符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == ';')
    {
        sym = SEMICOLON_SYM;
        printf("界符 <line %d, '%c'>\n", line, ch);
    }
    else if (ch == '.')
    {
        sym = PERIOD_SYM;
        printf("界符 <line %d, '%c'>\n", line, ch);
    }
}
