#include<iostream>
#include<string>
#include<sstream>
#include <cctype> 
#include <regex>
#include "Lexical.h"
#include"DataStruct.h"
using namespace std;

string KeyIdentAnalysis(string str, int state)
{
	//if (str == "sourceFile")
	//{
	//	return "";
	//}
	if (KeywordAnalysis(str))
		return '\n'+ str + ",�ؼ���\n";
	else
		return '\n'+str + ",��ʶ��\n";
}
string OtherAnalysis(string str, int state)
{
	char ch = str[0];
	if (state == 2 && OperatorAnalysis(str))
	{
		return  '\n' + str + ", ������\n";
	}
	else if (state == 3 && SeparatorAnlysis(ch))
	{
		return '\n' + str + ",�ָ���\n";
	}
	else if ((state == 4 || state == 6 || state == 7) && NumberAnalysis(str))
	{
		return '\n' + str + ",����\n";
	}
	else if (state == 5 && StringAnlysis(str))
	{
		return '\n' + str + ",�ַ���\n";
	}
		return '\n' + str + ",δ����\n";
}
// �ؼ��ִʷ�����
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
// ��ʶ���ʷ�����
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
// ���ִʷ�����
bool NumberAnalysis(string strNum)
{
	regex numberPattern(R"(([-+]?\d+(\.\d*)?([eE][-+]?\d+)?)|([-+]?\.\d+([eE][-+]?\d+)?))");
	return regex_match(strNum, numberPattern);
}
// ������ʷ�����
bool OperatorAnalysis(string strOperator)
{
	for (int i = 0; i < OperatorNum; i++) {
		if (strOperator == Operator[i]) {
			return true;
		}
	}
	return false;
}
// �ָ����ʷ�����
bool SeparatorAnlysis(char strOperator)
{
	for (int i = 0; i < SeparatorNum; i++) {
		if (strOperator == Separator[i]) {
			return true;
		}
	}
	return false;
}
//�ַ����������ʷ�����
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
//�ж��Ƿ�����ĸ
bool Letter(char ch)
{
	string str = "";
	str += ch;
	regex numberPattern("[a-zA-Z]");
	return regex_match(str, numberPattern);
}
//�ж��Ƿ�������
bool Number(char ch)
{
	return isdigit((unsigned char)ch);
}

bool Operate(char ch)
{
	for (int i = 0; i < OperatorNum; i++) 
		for(int j=0;j<2;j++)
		if (ch == Operator[i][j]) {
			return true;
		}
	
	return false;
}
