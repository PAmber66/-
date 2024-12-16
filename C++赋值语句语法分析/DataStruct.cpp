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
    "+", "-", "*", "/", "%",  // ���������
    "++", "--",               // ����/�Լ������
    "+=", "-=", "*=", "/=", "%=",  // ��ֵ��������������������ϣ�
    "=", "==", "!=",          // �Ƚ������
    ">", "<", ">=", "<=",     // ��ϵ�����
    "&&", "||", "!",          // �߼������
    "&", "|", "^", "~",       // λ�����
    "<<", ">>",               // ��λ�����
    "?:",                     // ��Ԫ���������
    "=", "->", ".",           // ��Ա���������
    //"[]", "()",               // �±�ͺ������������
    "&", "*", "#"             // ��ַ�������������
};
char Separator[SeparatorNum] = { ';', ',', '(', ')', '{', '}', '[', ']' };

map<string, int> SIGN;
vector<string> Order;