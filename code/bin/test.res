词法分析结果：
保留字 <line 1, 'var'>
标识符 <line 1, 'x'>
界符 <line 1, ','>
标识符 <line 1, 'y'>
界符 <line 1, ';'>
保留字 <line 4, 'begin'>
标识符 <line 4, 'x'>
运算符 <line 4, ':='>
数字 <line 4, 5>
界符 <line 4, ';'>
标识符 <line 5, 'y'>
运算符 <line 5, ':='>
数字 <line 5, 6>
界符 <line 5, ';'>
保留字 <line 6, 'write'>
界符 <line 6, '('>
标识符 <line 6, 'x'>
界符 <line 6, ','>
标识符 <line 6, 'y'>
界符 <line 6, ')'>
保留字 <line 7, 'end'>
界符 <line 7, ';'>
界符 <line 7, '.'>
程序源代码：
 var x,y;

begin
    x:= 5;
    y:= 6;
    write(x,y)
end;
生成目标代码：
JMP 0 1
INT 0 3
LIT 0 5
STO 0 3
LIT 0 6
STO 0 4
LOD 0 3
OPR 0 13
LOD 0 4
OPR 0 13
OPR 0 0
解释执行结果：
5
6
