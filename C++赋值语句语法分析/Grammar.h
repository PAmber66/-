#pragma once
#include<iostream>
#include<map>
#include<string>
using namespace std;

//LL1预测分析表
extern map<pair<string, string>, string> LL1;
//初始化LL1预测分析表
void LL1_map_init();
//对源程序做赋值语句语法分析
void GrammarAnalysis();