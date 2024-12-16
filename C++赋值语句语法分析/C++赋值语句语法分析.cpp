#include <iostream>
#include<fstream>
#include<string>
#include"Lexical.h"
#include"Grammar.h"
using namespace std;

/*基于LL(1)文法
 * 此程序为C++语言的赋值语句的语法分析程序
 * 因为只做了赋值语句的语法分析程序，因此无法分析出赋值语句中有函数调用的情况
 * 如：int a=str.length();
 * 应当在输入文件中避免这种情况，否则会报错退出
 * 此外，本分析程序只能分析出一维数组，更高维度需要更多逻辑分析
 * 受时间限制，本分析程序没有维护一个栈来分析作用域
*/
int main()
{
	ifstream sourceFile("C:\\Users\\70708\\source\\repos\\C++赋值语句语法分析\\语法分析源程序.txt");
	if (sourceFile.is_open()) {
		char ch;
		// 因为只需要分析赋值语句，因此只存储与赋值语句有关的状态，其余状态用0表示
		// 初始状态，-1
		// 存储int型标识符，状态1
		//存储其他数形标识符，状态2
		// 存储字符型标识符，状态3
		// 存储字符串型标识符，状态4
		// 存储指针型标识符，状态5
		//存储整形，状态6
		//存储字符串字面量，状态9
		//存储浮点数，状态8
		//存储负整数，状态7
		string strTemp = "";		// 分析栈，用于暂时存储
		string strinput = "";
		int strstate = -1;		//状态,-1表示状态为初始状态，同时分析栈里为空
		// 读到文件结尾停止
		while (!sourceFile.eof()) {
			ch = sourceFile.get();
			Lexical(ch, &strTemp, &strstate);
		}
		LL1_map_init();
		GrammarAnalysis();
		sourceFile.close();

	} 
	else if (!sourceFile.is_open())
	{
		cout << "打开source文件失败！" << endl;
	}

	return 0;
}