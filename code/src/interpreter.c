#include "headers/interpreter.h"

int base(int stack[], int currentLevel, int levelDiff)
{
    int b = currentLevel;

    while (levelDiff--)
        b = stack[b];
    return b;
}

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
        case LIT:             // a放到栈顶
            stack[++t] = i.a; // t表示栈顶
            break;
        case OPR:
            switch (i.a) // a 具体操作内容
            {
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
                    printf("Error: Divided by zero.\n");
                    continue;
                }
                stack[t] /= stack[t + 1];
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
            case OPR_LEQ:
                t--;
                stack[t] = stack[t] <= stack[t + 1];
            }
            break;
        case OPR_GTR:
            t--;
            stack[t] = stack[t] > stack[t + 1];
            break;
        case OPR_GEQ:
            t--;
            stack[t] = stack[t] >= stack[t + 1];

        case LOD:
            stack[++t] = stack[base(stack, b, i.l) + i.a]; // a相对寻址
            break;
        case STO: // 栈顶内容送到某个单元
            stack[base(stack, b, i.l) + i.a] = stack[t];
            t--;
            break;
        case CAL: // 调用过程
            stack[t + 1] = base(stack, b, i.l);
            stack[t + 2] = b;
            stack[t + 3] = pc;
            b = t + 1;
            pc = i.a;
            break;
        case INT: // 局部量个数+a
            t += i.a;
            break;
        case JMP: // 无条件转移
            pc = i.a;
            break;
        case JPC: // 条件转移，栈顶为0（非真）时转移
            if (stack[t] == 0)
                pc = i.a;
            t--; // 顺序执行
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