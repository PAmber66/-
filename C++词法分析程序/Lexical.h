#pragma once
#include<iostream>
#include"DataStruct.h"
using namespace std;

//关键词和标识符词法分析
string KeyIdentAnalysis(string str, int state);
//其他词法分析
string OtherAnalysis(string str, int state);
// 关键字词法分析
bool KeywordAnalysis(string strKeyword);
// 标识符词法分析
bool IdentAnalysis(string strIdent);
// 数字词法分析
bool NumberAnalysis(string strNum);
// 运算符词法分析
bool OperatorAnalysis(string strOperator);
// 分隔符词法分析
bool SeparatorAnlysis(char strBaundary);
//字符串词法分析
bool StringAnlysis(string strBaundary);
//判断是不是字母
bool Letter(char ch);
//判断是不是数字
bool Number(char ch);
//判断是不是运算符
bool Operate(char ch);