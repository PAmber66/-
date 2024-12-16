#include<iostream>
#include<string>
#include<sstream>
#include <cctype> 
#include <regex>
#include "Lexical.h"
#include"DataStruct.h"
using namespace std;


//�ؼ��ʺͱ�ʶ���ʷ�����
int KeyIdentAnalysis(string str)
{
	if (KeywordAnalysis(str))
		return KeyState;
	else
		return IntState;
}
//�����ʷ�����
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
//�ж��ǲ��������
bool Operate(char ch)
{
	for (int i = 0; i < OperatorNum; i++)
		for (int j = 0; j < 2; j++)
			if (ch == Operator[i][j]) {
				return true;
			}

	return false;
}
//����ֵ�Բ�����ű�
void Insert(string str, int state)
{
	if (state!=UselessState)
	{
		if (state == IntState)//����Ǳ�ʶ������Ӧ�ò鿴�Լ�ǰ�����û�йؼ����������Լ�������
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
			Order.push_back(str);					//���Ǳ�ʶ�������ö����ж�
			SIGN.insert({ str, state });						//���Ѿ��жϵĵ��ʼ�����ű�
		}
	}
}
//�ʷ���������
void Lexical(char ch, string* strTemp, int* strstate)
{
// �洢�ؼ���,״̬0
//�洢��ʶ����״̬1
// �洢��������״̬2
// �洢�ָ�����״̬3
//�洢���Σ�״̬4
//�洢�ַ�����������״̬5
//�洢��������״̬6
//�洢��������״̬7
//�洢���飬״̬8
	//���������жϣ�����ʶ�����
	string Temp = *strTemp;
	//if (Temp == "wordIndex")
	//	int i=0;
	if (*strstate == 5 && ch != '\'' && ch != '\"')
	{
		*strTemp += ch;
	}
	//������ĸ�����»���
	else if (Letter(ch) || ch == '_')
	{
		if (*strstate == -1)//����ǳ�ʼ״̬�����ʼ��
		{
			*strTemp += ch;
			*strstate = 0;
		}
		else if (*strstate == 0 || *strstate == 1 || *strstate == 5)//����ǹؼ��ֻ��ʶ�����ַ���������״̬����ֱ������
		{
			*strTemp += ch;
		}
		else
		{
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
			*strTemp = "";							  //���������ʱ�洢�ķ���ջ
			*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			*strTemp += ch;
			*strstate = 0;
		}
	}
	//��������
	else if (Number(ch))
	{
		if (*strstate == -1)//����ǳ�ʼ״̬�����ʼ��
		{
			*strTemp += ch;
			*strstate = 4;
		}
		else if (*strstate == 4 || *strstate == 0 || *strstate == 1 || *strstate == 5 || *strstate == 6 || *strstate == 7)//��������ֻ��߹ؼ��ֻ��ʶ�����ַ���������״̬����ֱ������
		{
			*strTemp += ch;
		}
		else
		{
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
			*strTemp = "";							  //���������ʱ�洢�ķ���ջ
			*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			*strTemp += ch;
			*strstate = 4;
		}
	}
	//����'����"
	else if (ch == '\'' || ch == '\"')
	{
		if (*strstate == -1)//����ǳ�ʼ״̬�����ʼ��
		{
			*strTemp += ch;
			*strstate = 5;
		}
		else if (*strstate == 5)//�����ʼ�����ַ���״̬��˵����������п����ǽ���
		{
			if (ch == '\'' &&  Temp[0] == '\'')
			{
				*strTemp += ch;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			}
			else if (ch == '\"' && Temp[0] == '\"')
			{
				*strTemp += ch;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			}
			else
			{
				*strTemp += ch;
			}
		}
		else if (*strstate == 0)
		{
			Insert(*strTemp, KeyIdentAnalysis(*strTemp));//����ֵ�Բ�����ű�
			*strTemp = "";								//��շ���ջ
			*strTemp += ch;							  //������ʱ�洢�ķ���ջ����ch
			*strstate = 5;							  //ͬʱ��״̬��Ϊ�ַ���
		}
	}
	//�����ָ������߿ո���س�
	else if (SeparatorAnlysis(ch) || ch == ' ' || ch == '\n' || ch == '\t')
	{
		//����ǿո񣬻��з������Ʊ��
		if (ch == ' ' || ch == '\n' || ch == '\t')
		{
			if(*strstate == -1)
			{
				return;
			}
			else if (*strstate == 0)
			{

				Insert(*strTemp, KeyIdentAnalysis(*strTemp));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;
			}
		}
		//����Ƿָ���
		else
		{
			if (*strstate == -1)//����ǳ�ʼ״̬����ֱ�ӽ��ָ����������봮
			{
				*strTemp += ch;
				*strstate = 3;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			}
			else if (*strstate == 0)//���֮ǰ�ǹؼ��ֻ��߱�ʶ��״̬
			{
				if (ch == '[')
				{
					*strTemp += ch;
					*strstate = 8;
				}
				else if (ch == ']' && *strstate == 8)
				{
					*strTemp += ch;
					Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
					*strTemp = "";							  //���������ʱ�洢�ķ���ջ
					*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
				}
				else
				{
					Insert(*strTemp, KeyIdentAnalysis(*strTemp));//����ֵ�Բ�����ű�
					*strTemp = ch;							  //���������ʱ�洢�ķ���ջ�����ҽ�����ַ�����
					*strstate = 3;
					Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
					*strTemp = "";							  //���������ʱ�洢�ķ���ջ
					*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
				}
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = ch;							  //���������ʱ�洢�ķ���ջ
				*strstate = 3;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;
			}
		}
		int a = -1, b;
		b = a + -8;
	}
	//����ǲ�����
	else if (Operate(ch))
	{
		//"."��Ҫ�����жϣ���Ϊ�и��������ڵĿ���
		if (ch == '.')
		{
			if (*strstate == 4 || *strstate == 7)
			{
				*strTemp += ch;
				*strstate = 6;//��Ϊ������
			}
			else if (*strstate == 5)
			{
				*strTemp += ch;
			}
		}
		else if (*strstate == -1)//����ǳ�ʼ״̬�����ʼ��
		{
			if (ch == '-')
			{
				*strTemp = ch;//�Ǹ�����
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		else if (*strstate == 0)//���֮ǰ�ǹؼ��ֻ��߱�ʶ��״̬
		{
			Insert(*strTemp, KeyIdentAnalysis(*strTemp));//����ֵ�Բ�����ű�
			//���ﲻ���ж��Ƿ��Ǹ�������Ϊ���Ž����ڱ�ʶ����
			if (ch == '-')
			{
				*strTemp = ch;//�Ǹ�����
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		else if (*strstate == 2 || Temp[0] == '-')//���֮ǰ���ǲ�����״̬
		{
			if (OperatorAnalysis(*strTemp + ch))
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";
				*strstate = -1;
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				if (ch == '-')
				{
					*strTemp = ch;//�Ǹ�����
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
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
			if (ch == '-')
			{
				*strTemp = ch;//�Ǹ�����
				*strstate = 7;
			}
			else
			{
				*strTemp = ch;
				*strstate = 2;
			}
		}
		}
		//������������
	else
	{
		if (*strstate == -1)//����ǳ�ʼ״̬�����ʼ��
		{
			*strTemp += ch;
			*strstate = 2;
		}
		else if (*strstate == 2)
		{
			*strTemp += ch;
			Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
			*strTemp = "";							  //���������ʱ�洢�ķ���ջ
			*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
		}
		else
		{
			if (*strstate == 0)//���֮ǰ�ǹؼ��ֻ��߱�ʶ��״̬
			{
				Insert(*strTemp, KeyIdentAnalysis(*strTemp));//����ֵ�Բ�����ű�
				*strTemp = ch;							  //���������ʱ�洢�ķ���ջ�����ҽ�����ַ�����
				*strstate = 2;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;							  //ͬʱ��״̬�ָ�Ϊ��ʼ״̬
			}
			else
			{
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = ch;							  //���������ʱ�洢�ķ���ջ
				*strstate = 2;
				Insert(*strTemp, OtherAnalysis(*strTemp, *strstate));//����ֵ�Բ�����ű�
				*strTemp = "";							  //���������ʱ�洢�ķ���ջ
				*strstate = -1;
			}
		}
		}
}
