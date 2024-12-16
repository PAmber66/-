#include<iostream>
#include<map>
#include<string>
#include<stack>
#include<queue>
#include"Grammar.h"
#include"DataStruct.h"
using namespace std;

//LL1Ԥ�������
map<pair<string, string>, string> LL1;


void LL1_map_init()
{
	//���ս����"E,E',T,T',F"
	// �ս����"+,-,*,/,%,(,),i,n,++,--,#"
	//E'��G����ʾ
	//T'��H����ʾ
	LL1[{"E", "i"}] = "TG";
	LL1[{"E", "("}] = "TG";
	LL1[{"E", "n"}] = "TG";
	LL1[{"G", "+" }] = "+TG";
	LL1[{"G", "-"}] = "-TG";
	LL1[{"G", ")"}] = "";
	LL1[{"G", "#"}] = "";
	LL1[{"T", "*"}] = "FH";
	LL1[{"T", "/"}] = "FH";
	LL1[{"T", "%"}] = "FH";
	LL1[{"T", "i"}] = "i";
	LL1[{"T", "n"}] = "n";
	LL1[{"H", "*"}] = "*FH";
	LL1[{"H", "/"}] = "/FH";
	LL1[{"H", "%"}] = "%FH";
	LL1[{"H", "("}] = "";
	LL1[{"H", ")"}] = "";
	LL1[{"F", "("}] = "(E)";
	LL1[{"F", "i"}] = "i";
	LL1[{"F", "n"}] = "n";
	LL1[{"F", "++"}] = "K";
	LL1[{"F", "--"}] = "K";
	LL1[{"K", "++"}] = "F++";
	LL1[{"K", "--"}] = "F--";
	LL1[{"K", "#"}] = "F";
}

void GrammarAnalysis()
{
	// ����״̬,��0��ʾ
	// �洢�ؼ��֣�״̬-1
	// �洢int�ͱ�ʶ����״̬1(��ʶ����Ĭ��״̬)
	//�洢�������α�ʶ����״̬2
	// �洢�ַ��ͱ�ʶ����״̬3
	// �洢�ַ����ͱ�ʶ����״̬4
	//�洢��������״̬6
	//�洢��������״̬7
	//�洢��������״̬8
	//�洢��������״̬9
	//�洢�ָ�����״̬10
	int size = Order.size();
	stack<string>analyStack;	// ����ջ
	queue<int>inputStack;	// ���봮,��״̬����
	string inputStr="";        //���봮������
	string staTop;				// ջ��Ԫ��
	analyStack.push("#");		// ��ʼ������ջ
	analyStack.push("E");
	for (const auto& pair : SIGN) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}
	for (int i = 0; i < size; i++)
	{
		string str = Order[i];
		if (str == "=" || str == "+=" || str == "-=" || str == "*=" || str == "/=" || str == "%=")
		{
			cout << "��ʼ������ֵ��䣺" << Order[i - 1] << " " << Order[i];
			int left = SIGN[Order[i - 1]];//��ʾ��ֵ����ߵı���������
			int j = ++i;
			int right = SIGN[Order[j]];//��ʾ��ֵ���ұߵı���������
			//��ʼ�����봮
			do {
				inputStr += Order[j];
				inputStack.push(right);
				j = ++i;
				right = SIGN[Order[j]];
			} while (right != semicolonState);//�����ֺŽ�������
			cout <<" "<< inputStr << endl;
			inputStr = "";
			inputStack.push('#');
			string str;//��ʾ����ʽ�Ķ���
			string Terminal;//��ʾ�ս��
			string Nonterminal;//��ʾ���ս��
			for (int j = 0; j < inputStack.size(); j++)
			{
				Nonterminal = analyStack.top();
				int now = inputStack.front();//���봮��ǰԪ�ص�״̬
				inputStack.pop();
				str = "";//����ʽ������ʼ��Ϊ��
				Terminal = "";//�ս����ʼ��Ϊ��
				//Ѱ���ս��
				if (now == 1 || now == 2 || now == 3 || now == 4)
					Terminal = 'i';
				else if (now == 6 || now == 7 || now == 8)
					Terminal = 'n';
				else if (now == 10)
					Terminal = '(';
				else if (now == 11)
					Terminal = ')';
				else if (now == 9)
					Terminal = Order[i + j];
				//Ԥ�����
				if (((left==1||left==2)&&(now==3||now==4))||((left==3||left==4)&&(now==1||now==2||now==6||now==7||now==8)))
				{
					cout << "��ֵ����﷨���󣬸�ֵ���������Ͳ�ƥ��" << Order[i - 1] << '\t' << Order[i + j]<<endl;
					break;
				}
				else if (Nonterminal == Terminal)
				{
					analyStack.pop();//����ջ����
					inputStack.pop();//���봮����
					cout << "����ʽƥ�䣺" << Nonterminal << "=" << Order[i + j]<<endl;
				}
				else if(LL1.count({Nonterminal,Terminal}))
				{
					str=LL1[{Nonterminal,Terminal}];
					analyStack.pop();
					if (str != "")
					{
						for (int h = str.size() - 1; h >= 0; h--)
						{
							if (str[h] == '+' || str[h] == '-')
							{
								analyStack.push(str.substr(h + 1, 2));//����'+'��'-'���ӵ�ǰλ�������ȡ2���ַ�
							}
							else
							{
								analyStack.push(str.substr(h, 1));//��ȡ��ǰ�ַ�
							}

						}
						cout << "��������ʽ" << Nonterminal << "->" << str <<endl;
					}
				}
			}
			cout << "������ֵ���������" << endl;
		}
	}
}