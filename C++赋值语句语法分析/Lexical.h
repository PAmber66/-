#pragma once
#include<iostream>
#include"DataStruct.h"
using namespace std;

//�ʷ���������
void Lexical(char ch, string* strTemp, int* strstate);
//�ؼ��ʺͱ�ʶ���ʷ�����
int KeyIdentAnalysis(string str);
//�����ʷ�����
int OtherAnalysis(string str, int state);
// �ؼ��ִʷ�����
bool KeywordAnalysis(string strKeyword);
// ��ʶ���ʷ�����
bool IdentAnalysis(string strIdent);
// ���ִʷ�����
bool NumberAnalysis(string strNum);
// ������ʷ�����
bool OperatorAnalysis(string strOperator);
// �ָ����ʷ�����
bool SeparatorAnlysis(char strBaundary);
//�ַ����ʷ�����
bool StringAnlysis(string strBaundary);
//�ж��ǲ�����ĸ
bool Letter(char ch);
//�ж��ǲ�������
bool Number(char ch);
//�ж��ǲ��������
bool Operate(char ch);
//����ֵ�Բ�����ű�
void Insert(string str,int state);