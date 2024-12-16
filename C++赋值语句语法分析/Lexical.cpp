#include<iostream>
#include<string>
#include<sstream>
#include <cctype> 
#include <regex>
#include "Lexical.h"
#include"DataStruct.h"
using namespace std;


//关键词和标识符词法分析
int KeyIdentAnalysis(string str)
{
	if (KeywordAnalysis(str))
		return KeyState;
	else
		return IntState;
}
//其他词法分析
int OtherAnalysis(string str, int state)
{
	char ch = str[0];
	if (state == 2 && OperatorAnalysis(str))
	{
		return OperateState;
	}
	else if (state == 3 && SeparatorAnlysis(ch))
	{
		if (ch == '(')
			return LeftSeperateState;
		else if (ch == ')')
			return rightSeperateState;
		else if (ch == ';')
			return semicolonState;
		else 
			return UselessState;
	}
	else if ((state == 4 || state == 6 || state == 7) && NumberAnalysis(str))
	{
		if (state == 4)
			return PositiveState;
		else if (state == 6)
			return FloatState;
		else if (state == 7)
			return NegtiveState;
	}
	else if (state == 5 && StringAnlysis(str))
	{
		return StringState;
	}
	else if (state == 8)
	{
		return IntState;
	}
	return UselessState;
}
// 关键字词法分析
bool KeywordAnalysis(string strKeyword)
{
	const char* strchar = strKeyword.c_str();
	char ch = strchar[0];
	if (ch >= 'a' && ch <= 'z') {
		for (int i = 0; i < KeywordNum; i++) {
			if (strKeyword == KeyWord[i]) {
				return true;
			}
		}
	}
	return false;
}
// 标识符词法分析
bool IdentAnalysis(string strIdent)
{
	const char* strchar = strIdent.c_str();
	char ch = strchar[0];
	if (ch >= 'a' && ch <= 'z')
	{
		for (int i = 0; i < KeywordNum; i++) {
			if (strIdent == KeyWord[i]) {
				return false;
			}
		}
	}
	else if ((ch >= 'A' && ch <= 'Z') || ch == '_')
	{
		regex identPattern("[a-zA-Z0-9_]+");
		return regex_match(strIdent, identPattern);
	}
	return false;
}
// 数字词法分析
bool NumberAnalysis(string strNum)
{
	regex numberPattern(R"(([-+]?\d+(\.\d*)?([eE][-+]?\d+)?)|([-+]?\.\d+([eE][-+]?\d+)?))");
	return regex_match(strNum, numberPattern);
}
// 运算符词法分析
bool OperatorAnalysis(string strOperator)
{
	for (int i = 0; i < OperatorNum; i++) {
		if (strOperator == Operator[i]) {
			return true;
		}
	}
	return false;
}
// 分隔符词法分析
bool SeparatorAnlysis(char strOperator)
{
	for (int i = 0; i < SeparatorNum; i++) {
		if (strOperator == Separator[i]) {
			return true;
		}
	}
	return false;
}
//字符串字面量词法分析
bool StringAnlysis(string Strings)
{
	int Length = (int)Strings.length();
	if (Length < 2)
		return false;
	else if (Strings[0] == '\'' && Strings[Length - 1] == '\'')
		return true;
	else if (Strings[0] == '\"' && Strings[Length - 1] == '\"')
		return true;
	else
		return false;
}
//判断是否是字母
bool Letter(char ch)
{
	string str = "";
	str += ch;
	regex numberPattern("[a-zA-Z]");
	return regex_match(str, numberPattern);
}
//判断是否是数字
bool Number(char ch)
{
	return isdigit((unsigned char)ch);
}
//判断是不是运算符
bool Operate(char ch)
{
	for (int i = 0; i < OperatorNum; i++)
		for (int j = 0; j < 2; j++)
			if (ch == Operator[i][j]) {
				return true;
			}

	return false;
}
//将键值对插入符号表
void Insert(string str, int state)
{
	if (state!=UselessState)
	{
		if (state == IntState)//如果是标识符，则应该查看自己前面的有没有关键字来定义自己的类型
		{
			string judge = Order.back();
			Order.push_back(str);
			if (judge == "int")
			{
				SIGN.insert({ str,IntState });
			}
			else if (judge == "char")
			{
				SIGN.insert({ str,CharState });
			}
			else if (judge == "string")
			{
				SIGN.insert({ str,StringState });
			}
			else if (judge == "float" || judge == "long" || judge == "double" || judge == "short")
			{
				SIGN.insert({ str,OtherNumberState });
			}
		}
		else
		{
			Order.push_back(str);					//不是标识符，不用额外判断
			SIGN.insert({ str, state });						//将已经判断的单词加入符号表
		}
	}
}
//词法分析程序
void Lexical(char ch, string* strTemp, int* strstate)
{
// 存储关键字,状态0
//存储标识符，状态1
// 存储操作符，状态2
// 存储分隔符，状态3
//存储整形，状态4
//存储字符串字面量，状态5
//存储浮点数，状态6
//存储负整数，状态7
//存储数组，状态8
	//增加特殊判断，避免识别出错
	string Temp = *strTemp;
	//if (Temp == "wordIndex")
	//	int i=0;
	if (*strstate == 5 && ch != '\'' && ch != '\"')
	{
		*strTemp += ch;
	}
	//读到字母或者下划线
	else if (Letter(ch) || ch == '_')
	{
		if (*strstate == -1)//如果是初始状态，则初始化
		{
			*strTemp += ch;
			*strstate = 0;
		}
		else if (*strstate == 0 || *strstate == 1 || *strstate == 5)//如果是关键字或标识符或字符串字面量状态，则直接增加
		{
			*strTemp += ch;
		}
		else
		{
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
			*strTemp = "";							  //清空用于暂时存储的分析栈
			*strstate = -1;							  //同时将状态恢复为初始状态
			*strTemp += ch;
			*strstate = 0;
		}
	}
	//读到数字
	else if (Number(ch))
	{
		if (*strstate == -1)//如果是初始状态，则初始化
		{
			*strTemp += ch;
			*strstate = 4;
		}
		else if (*strstate == 4 || *strstate == 0 || *strstate == 1 || *strstate == 5 || *strstate == 6 || *strstate == 7)//如果是数字或者关键字或标识符或字符串字面量状态，则直接增加
		{
			*strTemp += ch;
		}
		else
		{
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
			*strTemp = "";							  //清空用于暂时存储的分析栈
			*strstate = -1;							  //同时将状态恢复为初始状态
			*strTemp += ch;
			*strstate = 4;
		}
	}
	//读到'或者"
	else if (ch == '\'' || ch == '\"')
	{
		if (*strstate == -1)//如果是初始状态，则初始化
		{
			*strTemp += ch;
			*strstate = 5;
		}
		else if (*strstate == 5)//如果开始就是字符串状态，说明这个符号有可能是结束
		{
			if (ch == '\'' &&  Temp[0] == '\'')
			{
				*strTemp += ch;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;							  //同时将状态恢复为初始状态
			}
			else if (ch == '\"' && Temp[0] == '\"')
			{
				*strTemp += ch;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;							  //同时将状态恢复为初始状态
			}
			else
			{
				*strTemp += ch;
			}
		}
		else if (*strstate == 0)
		{
			Insert(*strTemp, KeyIdentAnalysis(*strTemp));//将键值对插入符号表
			*strTemp = "";								//清空分析栈
			*strTemp += ch;							  //用于暂时存储的分析栈存入ch
			*strstate = 5;							  //同时将状态置为字符串
		}
	}
	//读到分隔符或者空格与回车
	else if (SeparatorAnlysis(ch) || ch == ' ' || ch == '\n' || ch == '\t')
	{
		//如果是空格，换行符或者制表符
		if (ch == ' ' || ch == '\n' || ch == '\t')
		{
			if(*strstate == -1)
			{
				return;
			}
			else if (*strstate == 0)
			{

				Insert(*strTemp, KeyIdentAnalysis(*strTemp));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;							  //同时将状态恢复为初始状态
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;
			}
		}
		//如果是分隔符
		else
		{
			if (*strstate == -1)//如果是初始状态，则直接将分隔符送入输入串
			{
				*strTemp += ch;
				*strstate = 3;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;							  //同时将状态恢复为初始状态
			}
			else if (*strstate == 0)//如果之前是关键字或者标识符状态
			{
				if (ch == '[')
				{
					*strTemp += ch;
					*strstate = 8;
				}
				else if (ch == ']' && *strstate == 8)
				{
					*strTemp += ch;
					Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
					*strTemp = "";							  //清空用于暂时存储的分析栈
					*strstate = -1;							  //同时将状态恢复为初始状态
				}
				else
				{
					Insert(*strTemp, KeyIdentAnalysis(*strTemp));//将键值对插入符号表
					*strTemp = ch;							  //清空用于暂时存储的分析栈，并且将这个字符加入
					*strstate = 3;
					Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
					*strTemp = "";							  //清空用于暂时存储的分析栈
					*strstate = -1;							  //同时将状态恢复为初始状态
				}
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = ch;							  //清空用于暂时存储的分析栈
				*strstate = 3;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;
			}
		}
		int a = -1, b;
		b = a + -8;
	}
	//如果是操作符
	else if (Operate(ch))
	{
		//"."需要特殊判断，因为有浮点数存在的可能
		if (ch == '.')
		{
			if (*strstate == 4 || *strstate == 7)
			{
				*strTemp += ch;
				*strstate = 6;//变为浮点数
			}
			else if (*strstate == 5)
			{
				*strTemp += ch;
			}
		}
		else if (*strstate == -1)//如果是初始状态，则初始化
		{
			if (ch == '-')
			{
				*strTemp = ch;//是负整数
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		else if (*strstate == 0)//如果之前是关键字或者标识符状态
		{
			Insert(*strTemp, KeyIdentAnalysis(*strTemp));//将键值对插入符号表
			//这里不用判断是否是负数，因为负号紧跟在标识符后
			if (ch == '-')
			{
				*strTemp = ch;//是负整数
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		else if (*strstate == 2 || Temp[0] == '-')//如果之前就是操作符状态
		{
			if (OperatorAnalysis(*strTemp + ch))
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";
				*strstate = -1;
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				if (ch == '-')
				{
					*strTemp = ch;//是负整数
					*strstate = 7;
				}
				else
				{
					*strTemp = ch;
					*strstate = 2;
				}
			}

		}
		else
		{
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
			if (ch == '-')
			{
				*strTemp = ch;//是负整数
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		}
		//读到其他符号
	else
	{
		if (*strstate == -1)//如果是初始状态，则初始化
		{
			*strTemp += ch;
			*strstate = 2;
		}
		else if (*strstate == 2)
		{
			*strTemp += ch;
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
			*strTemp = "";							  //清空用于暂时存储的分析栈
			*strstate = -1;							  //同时将状态恢复为初始状态
		}
		else
		{
			if (*strstate == 0)//如果之前是关键字或者标识符状态
			{
				Insert(*strTemp, KeyIdentAnalysis(*strTemp));//将键值对插入符号表
				*strTemp = ch;							  //清空用于暂时存储的分析栈，并且将这个字符加入
				*strstate = 2;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;							  //同时将状态恢复为初始状态
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = ch;							  //清空用于暂时存储的分析栈
				*strstate = 2;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//将键值对插入符号表
				*strTemp = "";							  //清空用于暂时存储的分析栈
				*strstate = -1;
			}
		}
		}
}
