词法分析结果：
保留字 <line 1, 'const'>
标识符 <line 1, 'a'>
运算符 <line 1, '='>
数字 <line 1, 101>
界符 <line 1, ';'>
保留字 <line 2, 'var'>
标识符 <line 2, 'b'>
界符 <line 2, ','>
标识符 <line 2, 'c'>
界符 <line 2, ';'>
保留字 <line 3, 'procedure'>
标识符 <line 3, 'p'>
界符 <line 3, ';'>
保留字 <line 5, 'begin'>
标识符 <line 5, 'c'>
运算符 <line 5, ':='>
标识符 <line 5, 'b'>
运算符<line 5, '+'>
标识符 <line 5, 'a'>
界符 <line 5, ';'>
保留字 <line 6, 'end'>
界符 <line 6, ';'>
界符 <line 6, '.'>
程序源代码：
 const a=101;
var b,c;
procedure p;
begin
  c:=b+a;
end;
生成目标代码：
JMP 0 8
JMP 0 2
INT 0 3
LOD 1 3
LIT 0 101
OPR 0 1
STO 1 4
OPR 0 0
INT 0 3
OPR 0 0
解释执行结果：
0
