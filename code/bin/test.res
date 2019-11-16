词法分析结果：
保留字 <line 1, 'const'>
标识符 <line 1, 'num'>
运算符 <line 1, '='>
数字 <line 1, 5>
界符 <line 1, ';'>
保留字 <line 2, 'var'>
标识符 <line 2, 'x'>
界符 <line 2, ','>
标识符 <line 2, 'y'>
界符 <line 2, ';'>
保留字 <line 5, 'begin'>
标识符 <line 5, 'x'>
运算符 <line 5, ':='>
标识符 <line 5, 'num'>
界符 <line 5, ';'>
保留字 <line 6, 'write'>
界符 <line 6, '('>
标识符 <line 6, 'x'>
界符 <line 6, ')'>
保留字 <line 7, 'end'>
错误<line: 7, error: 25, There should be a ')' to follow identifier.>
界符 <line 7, ';'>
界符 <line 7, '.'>
程序源代码：
const num = 5;
var x,y;

begin
    x:=num;
    write(x)
end;
生成目标代码：
JMP 0 1
INT 0 3
LIT 0 5
STO 0 3
LOD 0 3
OPR 0 13
OPR 0 0
解释执行结果：
5
