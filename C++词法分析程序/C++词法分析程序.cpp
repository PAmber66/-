#include <iostream>
#include<fstream>
#include<string>
#include"Lexical.h"

using namespace std;

/*
 * 此程序为C++语言的词法分析程序
*/
int main()
{
	ifstream sourceFile("C:\\Users\\70708\\source\\repos\\C++词法分析程序\\词法分析源程序.txt");
	ofstream targetFile("C:\\Users\\70708\\source\\repos\\C++词法分析程序\\词法分析生成序列.txt");

	if (sourceFile.is_open() && targetFile.is_open()) 
	{
		char ch;
		// 存储关键字,状态0
		//存储标识符，状态1
		// 存储操作符，状态2
		// 存储分隔符，状态3
		//存储整形，状态4
		//存储字符串字面量，状态5
		//存储浮点数，状态6
		//存储负整数，状态7
		string strTemp = "";		// 分析栈，用于暂时存储
		string strinput = "";
		int strstate = -1;		//状态,-1表示状态为初始状态，同时分析栈里为空
		targetFile << "词法分析结果序列格式如下： 单词，类型 " << endl;

		// 读到文件结尾停止
		while (!sourceFile.eof()) {
			ch = sourceFile.get();
			//增加特殊判断，避免识别出错
			if (strstate == 5&&ch!='\''&&ch!='\"')
			{
				strTemp += ch;
			}
			//读到字母或者下划线
			else if (Letter(ch) || ch == '_')
			{
				if (strstate == -1)//如果是初始状态，则初始化
				{
					strTemp += ch;
					strstate = 0;
				}
				else if (strstate == 0 || strstate == 1 || strstate == 5)//如果是关键字或标识符或字符串字面量状态，则直接增加
				{
					strTemp += ch;
				}
				else
				{
					strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";							  //清空用于暂时存储的分析栈
					strstate = -1;							  //同时将状态恢复为初始状态
					strTemp += ch;
					strstate = 0;
				}
			}
			//读到数字
			else if (Number(ch))
			{
				if (strstate == -1)//如果是初始状态，则初始化
				{
					strTemp += ch;
					strstate = 4;
				}
				else if (strstate == 4 || strstate == 0 || strstate == 1 || strstate == 5 || strstate == 6 || strstate == 7)//如果是数字或者关键字或标识符或字符串字面量状态，则直接增加
				{
					strTemp += ch;
				}
				else
				{
					strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";							  //清空用于暂时存储的分析栈
					strstate = -1;							  //同时将状态恢复为初始状态
					strTemp += ch;
					strstate = 4;
				}
			}
			//读到'或者"
			else if (ch == '\'' || ch == '\"')
			{
				if (strstate == -1)//如果是初始状态，则初始化
				{
					strTemp += ch;
					strstate = 5;
				}
				else if (strstate == 5)//如果开始就是字符串状态，说明这个符号有可能是结束
				{
					if (ch == '\'' && strTemp[0] == '\'')
					{
						strTemp += ch;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;							  //同时将状态恢复为初始状态
					}
					else if (ch == '\"' && strTemp[0] == '\"')
					{
						strTemp += ch;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;							  //同时将状态恢复为初始状态
					}
					else
					{
						strTemp += ch;
					}
				}
				else if (strstate == 0)
				{
					strinput += KeyIdentAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";								//清空分析栈
					strTemp += ch;							  //用于暂时存储的分析栈存入ch
					strstate = 5;							  //同时将状态置为字符串
				}
			}
			//读到分隔符或者空格与回车
			else if (SeparatorAnlysis(ch) || ch == ' ' || ch == '\n' || ch == '\t')
			{
				//如果是空格，换行符或者制表符
				if(ch == ' ' || ch == '\n' || ch == '\t')
			{
				if (strstate == -1)
				{
					continue;
				}
				else if (strstate == 0)
				{
					strinput += KeyIdentAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";							  //清空用于暂时存储的分析栈
					strstate = -1;							  //同时将状态恢复为初始状态
				}
				else
				{
					strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";							  //清空用于暂时存储的分析栈
					strstate = -1;
				}
			}
				//如果是分隔符
				else
				{
					if (strstate == -1)//如果是初始状态，则直接将分隔符送入输入串
					{
						strTemp += ch;
						strstate = 3;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;							  //同时将状态恢复为初始状态
					}
					else if (strstate == 0)//如果之前是关键字或者标识符状态
					{
						strinput += KeyIdentAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = ch;							  //清空用于暂时存储的分析栈，并且将这个字符加入
						strstate = 3;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;							  //同时将状态恢复为初始状态
					}
					else
					{
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = ch;							  //清空用于暂时存储的分析栈
						strstate = 3;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;
					}
				}
				int a = -1,b;
				b = a + -8;
			}
			//如果是操作符
			else if (Operate(ch))
			{
				//"."需要特殊判断，因为有浮点数存在的可能
			  if (ch == '.')
			  {
				if (strstate == 4 || strstate == 7)
				{
					strTemp += ch;
					strstate = 6;//变为浮点数
				}
				else if (strstate == 5)
				{
					strTemp += ch;
				}
			  }
			  else if (strstate == -1)//如果是初始状态，则初始化
				{
					if (ch == '-')
					{
						strTemp = ch;//是负整数
						strstate = 7;
					}
					else 
					{
						strTemp = ch;
						strstate = 2;
					}
				}
				else if (strstate == 0)//如果之前是关键字或者标识符状态
				{
					strinput += KeyIdentAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					//这里不用判断是否是负数，因为负号紧跟在标识符后
					if (ch == '-')
					{
						strTemp = ch;//是负整数
						strstate = 7;
					}
					else
					{
						strTemp = ch;
						strstate = 2;
					}
				}
				else if (strstate == 2||strTemp[0]=='-')//如果之前就是操作符状态
				{
					if (OperatorAnalysis(strTemp + ch))
					{
						strinput += OtherAnalysis(strTemp + ch, strstate);//将已经判断的单词加入输入串
						strTemp = "";
						strstate = -1;
					}						
					else
					{
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						if (ch == '-')
						{
							strTemp = ch;//是负整数
							strstate = 7;
						}
						else
						{
							strTemp = ch;
							strstate = 2;
						}
					}

				}
				else
				{
					strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					if (ch == '-')
					{
						strTemp = ch;//是负整数
						strstate = 7;
					}
					else
					{
						strTemp = ch;
						strstate = 2;
					}
				}
			}
			//读到其他符号
			else
			{
				if (strstate == -1)//如果是初始状态，则初始化
				{
					strTemp += ch;
					strstate = 2;
				}
				else if (strstate == 2)
				{
					strTemp += ch;
					strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
					strTemp = "";							  //清空用于暂时存储的分析栈
					strstate = -1;							  //同时将状态恢复为初始状态
				}
				else
				{
					if (strstate == 0)//如果之前是关键字或者标识符状态
					{
						strinput += KeyIdentAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = ch;							  //清空用于暂时存储的分析栈，并且将这个字符加入
						strstate = 2;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;							  //同时将状态恢复为初始状态
					}
					else
					{
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = ch;							  //清空用于暂时存储的分析栈
						strstate = 2;
						strinput += OtherAnalysis(strTemp, strstate);//将已经判断的单词加入输入串
						strTemp = "";							  //清空用于暂时存储的分析栈
						strstate = -1;
					}
				}
			}
		}
		targetFile << strinput << endl;
		sourceFile.close();
		targetFile.close();

	}
	else if (!targetFile.is_open()) {
		cout << "打开target文件失败！" << endl;
	}
	else {
		cout << "打开source文件失败！" << endl;
	}

	return 0;
}

