#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

// ��Ϊֻ��Ҫ������ֵ��䣬���ֻ�洢�븳ֵ����йص�״̬������״̬��0��ʾ
#define UselessState 0
// �洢�ؼ��֣�״̬-1
#define KeyState -1
// �洢int�ͱ�ʶ����״̬1(��ʶ����Ĭ��״̬)
#define IntState 1
//�洢�������α�ʶ����״̬2
#define OtherNumberState 2
// �洢�ַ��ͱ�ʶ����״̬3
#define CharState 3
// �洢�ַ����ͱ�ʶ����״̬4
#define StringState 4
//�洢��������״̬6
#define FloatState 6
//�洢��������״̬7
#define PositiveState 7
//�洢��������״̬8
#define NegtiveState 8
//�洢��������״̬9
#define OperateState 9
//�洢�����ţ�״̬10
#define LeftSeperateState 10
//�洢�����ţ�״̬11
#define rightSeperateState 11
//�洢�ֺţ�״̬12
#define semicolonState 12

#define KeywordNum 63
#define OperatorNum 35
#define SeparatorNum 8 
#define GSIZE 13	// �ķ�����ʽ�ĸ���
#define SLRSIZE 20	// ״̬����

extern char KeyWord[KeywordNum][KeywordNum];
extern char Operator[OperatorNum][OperatorNum];
extern char Separator[SeparatorNum];
extern map<string, int> SIGN;//���ű�
extern vector<string> Order;//Դ����˳�������