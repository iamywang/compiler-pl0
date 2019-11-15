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
    t = 0;

    do
    {
        i = code[pc++];
        if (pc > cx || i.f >= 8)
            return;

        // printf("pc: %d, %d, %d, %d\n", pc, i.f, i.l, i.a);

        switch (i.f)
        {
        case LIT:             // a放到栈顶
            stack[++t] = i.a; // t表示栈顶
            break;
        case OPR:
            switch (i.a) // a 具体操作内容
            {
            case OPR_EXT:
                printf("%d\n", stack[t]);
                return;
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
                break;
            case OPR_GTR:
                t--;
                stack[t] = stack[t] > stack[t + 1];
                break;
            case OPR_GEQ:
                t--;
                stack[t] = stack[t] >= stack[t + 1];
            }

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

// int main()
// {
//     /*
//     JMP		0		10
//     JMP		0		2
//     INT		0		3
//     LIT		0		4
//     STO		1		3
//     LIT		0		10
//     LOD		1		3
//     OPR		0		1
//     STO		1		4
//     OPR		0		0
//     INT		0		5
//     CAL		0		2
//     OPR		0		0
//     */

//     char a[3];
//     int b, c;
//     cx = 13;

//     for (int k = 0; k < cx; k++)
//     {
//         int index = 7;
//         scanf("%s", &a);
//         scanf("%d", &b);
//         scanf("%d", &c);
//         while (strcmp(a, ins[index--]))
//             ;
//         code[k].f = index + 1;
//         code[k].l = b;
//         code[k].a = c;
//         // printf("%d, %d, %d\n", code[k].f, code[k].l, code[k].a);
//     }
//     interpret();
//     return 0;
// }