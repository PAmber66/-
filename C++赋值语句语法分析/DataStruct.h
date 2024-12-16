#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

// 因为只需要分析赋值语句，因此只存储与赋值语句有关的状态，其余状态用0表示
#define UselessState 0
// 存储关键字，状态-1
#define KeyState -1
// 存储int型标识符，状态1(标识符的默认状态)
#define IntState 1
//存储其他数形标识符，状态2
#define OtherNumberState 2
// 存储字符型标识符，状态3
#define CharState 3
// 存储字符串型标识符，状态4
#define StringState 4
//存储浮点数，状态6
#define FloatState 6
//存储正整数，状态7
#define PositiveState 7
//存储负整数，状态8
#define NegtiveState 8
//存储操作符，状态9
#define OperateState 9
//存储左括号，状态10
#define LeftSeperateState 10
//存储右括号，状态11
#define rightSeperateState 11
//存储分号，状态12
#define semicolonState 12

#define KeywordNum 63
#define OperatorNum 35
#define SeparatorNum 8 
#define GSIZE 13	// 文法产生式的个数
#define SLRSIZE 20	// 状态个数

extern char KeyWord[KeywordNum][KeywordNum];
extern char Operator[OperatorNum][OperatorNum];
extern char Separator[SeparatorNum];
extern map<string, int> SIGN;//符号表
extern vector<string> Order;//源程序顺序遍历表