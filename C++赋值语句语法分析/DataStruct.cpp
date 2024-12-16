#include "DataStruct.h"

char KeyWord[KeywordNum][KeywordNum] = {
    "char", "double", "enum", "float", "int", "long", "short", "signed",
    "struct", "union", "unsigned", "void", "bool", "wchar_t",
    "if", "else", "switch", "case", "default", "for", "do", "while", "break",
    "continue", "goto", "return",
    "auto", "extern", "register", "static", "mutable", "thread_local", "constexpr",
    "class", "private", "protected", "public", "virtual", "friend", "explicit",
    "new", "delete", "typename", "operator",
    "try", "catch", "throw",
    "const", "sizeof", "typedef", "volatile", "namespace", "using", "inline",
    "static_cast", "dynamic_cast", "const_cast", "reinterpret_cast"
};
char Operator[OperatorNum][OperatorNum] = {
    "+", "-", "*", "/", "%",  // 算术运算符
    "++", "--",               // 自增/自减运算符
    "+=", "-=", "*=", "/=", "%=",  // 赋值运算符（与算术运算符结合）
    "=", "==", "!=",          // 比较运算符
    ">", "<", ">=", "<=",     // 关系运算符
    "&&", "||", "!",          // 逻辑运算符
    "&", "|", "^", "~",       // 位运算符
    "<<", ">>",               // 移位运算符
    "?:",                     // 三元条件运算符
    "=", "->", ".",           // 成员访问运算符
    //"[]", "()",               // 下标和函数调用运算符
    "&", "*", "#"             // 地址、解引用运算符
};
char Separator[SeparatorNum] = { ';', ',', '(', ')', '{', '}', '[', ']' };

map<string, int> SIGN;
vector<string> Order;