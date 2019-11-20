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
    t = 100;

    stack[1] = stack[2] = stack[3] = 0;

    do
    {
        i = code[pc++];

        // printf("pc: %d, %s, %d, %d\n", pc, ins[i.f], i.l, i.a);

        switch (i.f)
        {
        case LIT:             // a放到栈顶
            stack[++t] = i.a; // t表示栈顶
            break;
        case OPR:
            switch (i.a) // a 具体操作内容
            {
            case OPR_EXT:
                t = b - 1;
                pc = stack[t + 3];
                b = stack[t + 2];
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
                    error(26);
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
                break;
            case OPR_LES:
                t--;
                stack[t] = stack[t] < stack[t + 1];
                break;
            case OPR_LEQ:
                t--;
                stack[t] = stack[t] <= stack[t + 1];
                break;
            case OPR_GTR:
                t--;
                stack[t] = stack[t] > stack[t + 1];
                break;
            case OPR_GEQ:
                t--;
                stack[t] = stack[t] >= stack[t + 1];
                break;
            case OPR_NEG:
                stack[t] = -stack[t];
                break;
            case OPR_RED:
                scanf("%d", &stack[++t]);
                break;
            case OPR_WRT:
                printf("%d\n", stack[t]);
                t--;
                break;
            }
            break;

        case LOD:
            stack[++t] = stack[base(stack, b, i.l) + i.a]; // a相对寻址
            // printf("LOD: %d, current top: %d\n",stack[t],t);
            break;
        case STO: // 栈顶内容送到某个单元
            // printf("STO: %d, current top: %d\n",stack[t],t);
            stack[base(stack, b, i.l) + i.a] = stack[t];
            t--;
            break;
        case CAL:                               // 调用过程
            stack[t + 1] = base(stack, b, i.l); // SL
            stack[t + 2] = b;                   // DL
            stack[t + 3] = pc;                  // RA
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
