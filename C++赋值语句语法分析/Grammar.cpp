#include<iostream>
#include<map>
#include<string>
#include<stack>
#include<queue>
#include"Grammar.h"
#include"DataStruct.h"
using namespace std;

//LL1预测分析表
map<pair<string, string>, string> LL1;


void LL1_map_init()
{
	//非终结符："E,E',T,T',F"
	// 终结符："+,-,*,/,%,(,),i,n,++,--,#"
	//E'用G来表示
	//T'用H来表示
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
	// 其余状态,用0表示
	// 存储关键字，状态-1
	// 存储int型标识符，状态1(标识符的默认状态)
	//存储其他数形标识符，状态2
	// 存储字符型标识符，状态3
	// 存储字符串型标识符，状态4
	//存储浮点数，状态6
	//存储正整数，状态7
	//存储负整数，状态8
	//存储操作符，状态9
	//存储分隔符，状态10
	int size = Order.size();
	stack<string>analyStack;	// 分析栈
	queue<int>inputStack;	// 输入串,用状态代替
	string inputStr="";        //输入串的内容
	string staTop;				// 栈顶元素
	analyStack.push("#");		// 初始化分析栈
	analyStack.push("E");
	for (const auto& pair : SIGN) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}
	for (int i = 0; i < size; i++)
	{
		string str = Order[i];
		if (str == "=" || str == "+=" || str == "-=" || str == "*=" || str == "/=" || str == "%=")
		{
			cout << "开始分析赋值语句：" << Order[i - 1] << " " << Order[i];
			int left = SIGN[Order[i - 1]];//表示赋值号左边的变量的类型
			int j = ++i;
			int right = SIGN[Order[j]];//表示赋值号右边的变量的类型
			//初始化输入串
			do {
				inputStr += Order[j];
				inputStack.push(right);
				j = ++i;
				right = SIGN[Order[j]];
			} while (right != semicolonState);//遇到分号结束输入
			cout <<" "<< inputStr << endl;
			inputStr = "";
			inputStack.push('#');
			string str;//表示产生式的动作
			string Terminal;//表示终结符
			string Nonterminal;//表示非终结符
			for (int j = 0; j < inputStack.size(); j++)
			{
				Nonterminal = analyStack.top();
				int now = inputStack.front();//输入串当前元素的状态
				inputStack.pop();
				str = "";//产生式动作初始化为空
				Terminal = "";//终结符初始化为空
				//寻找终结符
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
				//预测分析
				if (((left==1||left==2)&&(now==3||now==4))||((left==3||left==4)&&(now==1||now==2||now==6||now==7||now==8)))
				{
					cout << "赋值语句语法错误，赋值号左右类型不匹配" << Order[i - 1] << '\t' << Order[i + j]<<endl;
					break;
				}
				else if (Nonterminal == Terminal)
				{
					analyStack.pop();//分析栈析出
					inputStack.pop();//输入串析出
					cout << "产生式匹配：" << Nonterminal << "=" << Order[i + j]<<endl;
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
								analyStack.push(str.substr(h + 1, 2));//遇到'+'或'-'，从当前位置往后截取2个字符
							}
							else
							{
								analyStack.push(str.substr(h, 1));//截取当前字符
							}

						}
						cout << "触发产生式" << Nonterminal << "->" << str <<endl;
					}
				}
			}
			cout << "本条赋值语句分析完毕" << endl;
		}
	}
}