词法分析结果：
保留字 <line 1, 'const'>
标识符 <line 1, 'a'>
运算符 <line 1, '='>
数字 <line 1, 10>
界符 <line 1, ';'>
保留字 <line 2, 'var'>
标识符 <line 2, 'b'>
界符 <line 2, ','>
标识符 <line 2, 'c'>
界符 <line 2, ';'>
保留字 <line 5, 'begin'>
标识符 <line 5, 'b'>
运算符 <line 5, ':='>
标识符 <line 5, 'a'>
界符 <line 5, ';'>
标识符 <line 6, 'c'>
运算符 <line 6, ':='>
标识符 <line 6, 'a'>
运算符<line 6, '+'>
标识符 <line 6, 'a'>
界符 <line 6, ';'>
保留字 <line 7, 'write'>
界符 <line 7, '('>
标识符 <line 7, 'b'>
界符 <line 7, ','>
标识符 <line 7, 'c'>
界符 <line 7, ')'>
保留字 <line 8, 'end'>
界符 <line 8, ';'>
界符 <line 8, '.'>
程序源代码：
 const a = 10;
var b,c;

begin
    b := a;
    c := a + a;
    write(b,c)
end;
生成目标代码：
JMP 0 1
INT 0 3
LIT 0 10
STO 0 3
LIT 0 10
LIT 0 10
OPR 0 1
STO 0 4
LOD 0 3
OPR 0 13
LOD 0 4
OPR 0 13
OPR 0 0
解释执行结果：
pc: 1, JMP, 0, 1
pc: 2, INT, 0, 3
pc: 3, LIT, 0, 10
pc: 4, STO, 0, 3
pc: 5, LIT, 0, 10
pc: 6, LIT, 0, 10
pc: 7, OPR, 0, 1
pc: 8, STO, 0, 4
pc: 9, LOD, 0, 3
pc: 10, OPR, 0, 13
10
pc: 11, LOD, 0, 4
pc: 12, OPR, 0, 13
20
pc: 13, OPR, 0, 0
