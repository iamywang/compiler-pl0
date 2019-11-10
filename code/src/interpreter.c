#include "headers/interpreter.h"

void interpret()
{
    pc = 0;
    b = 1;
    t = 3;
    stack[1] = stack[2] = stack[3] = 0;

    do
    {
        i = code[pc++];
        switch (i.f)
        {
        case LIT:
            stack[++t] = i.a;
            break;
        case OPR:
            switch (i.a)
            {
            case OPR_RET:
                t = b - 1;
                pc = stack[t + 3];
                b = stack[t + 2];
                break;
            case OPR_NEG:
                stack[t] = -stack[t];
                break;
            case OPR_ADD:
                t--;
                stack[t] += stack[t + 1];
                break;
            case OPR_MIN:
                t--;
                stack[t] -= stack[t + 1];
                break;
            case OPR_MUL:
                t--;
                stack[t] *= stack[t + 1];
                break;
            case OPR_DIV:
                t--;
                if (stack[t + 1] == 0)
                {
                    printf("Runtime Error: Divided by zero.\n");
                    printf("Program terminated.\n");
                    continue;
                }
                stack[t] /= stack[t + 1];
                break;
            case OPR_ODD:
                stack[t] %= 2;
                break;
            case OPR_EQU:
                t--;
                stack[t] = stack[t] == stack[t + 1];
                break;
            case OPR_NEQ:
                t--;
                stack[t] = stack[t] != stack[t + 1];
            case OPR_LES:
                t--;
                stack[t] = stack[t] < stack[t + 1];
                break;
            case OPR_GEQ:
                t--;
                stack[t] = stack[t] >= stack[t + 1];
            case OPR_GTR:
                t--;
                stack[t] = stack[t] > stack[t + 1];
                break;
            case OPR_LEQ:
                t--;
                stack[t] = stack[t] <= stack[t + 1];
            } // switch
            break;
        case LOD:
            stack[++t] = stack[base(stack, b, i.l) + i.a];
            break;
        case STO:
            stack[base(stack, b, i.l) + i.a] = stack[t];
            printf("%d\n", stack[t]);
            t--;
            break;
        case CAL:
            stack[t + 1] = base(stack, b, i.l);
            // generate new block mark
            stack[t + 2] = b;
            stack[t + 3] = pc;
            b = t + 1;
            pc = i.a;
            break;
        case INT:
            t += i.a;
            break;
        case JMP:
            pc = i.a;
            break;
        case JPC:
            if (stack[t] == 0)
                pc = i.a;
            t--;
            break;
        }
    } while (pc);
}

int main()
{
    // test
    /*
    int  0  3
    lod  1  3
    lit  0  10
    opr  0  2
    sto  1  4
    opr  0  0
    */

    printf("Begin Test EXEC. \n");

    code[0].f = INT;
    code[0].l = 0;
    code[0].a = 3;

    code[1].f = LOD;
    code[1].l = 1;
    code[1].a = 3;

    code[2].f = LIT;
    code[2].l = 0;
    code[2].a = 10;

    code[3].f = OPR;
    code[3].l = 0;
    code[3].a = 2;

    code[4].f = STO;
    code[4].l = 1;
    code[4].a = 4;

    code[5].f = OPR;
    code[5].l = 0;
    code[5].a = 0;

    interpret();

    printf("Finish Test EXEC. \n");

    return 0;
}