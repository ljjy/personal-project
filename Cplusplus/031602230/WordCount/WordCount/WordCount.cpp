#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
int line_count = 0;
int word_count = 0;
int allcount = 0;

bool check_isChar(char s1)
{
	if ((s1 >= 'a'&&s1 <= 'z') || (s1 >= 'A'&&s1 <= 'Z'))return true;
	else return false;
}
bool check_isVal(char s1)
{
	if ((s1 >= 'a'&&s1 <= 'z') || (s1 >= 'A'&&s1 <= 'Z') || (s1 >= '0'&&s1 <= '9'))return true;
	else return false;
}
bool check(string str)
{
	if (str.length() <= 3)return false;
	if (!(check_isChar(str[0]) && check_isChar(str[1]) && check_isChar(str[2]) && check_isChar(str[3])))return false;
	for (int i = 4; i < str.length(); i++)
	{
		if (!check_isVal(str[i]))return false;
	}
	return true;
}
int count_Ascii(string pth)			//计算总字符数
{
	fstream f(pth);
	char c;
	int count = 0;
	while (f.get(c))count++;
	return count;
}
int count_Line(string pth)			//计算总行数
{
	string str;
	fstream f(pth);
	int line_count = 0;
	while (getline(f, str))
	{
		if (str != " " && str != "\t" && str != "\n")line_count++;
		else continue;
	}
	return line_count;
}
unordered_map<string, int> strMap;  //保存的结果
void count_Frequency(string strTmp)
{
	unordered_map<string, int>::iterator it = strMap.find(strTmp);
	if (it == strMap.end()) //strMap中如果不存在当前单词则插入一个新键值对，出现频率为1
	{
		strMap.insert(unordered_map<string, int>::value_type(strTmp, 1));
	}
	else                   //如果存在则出现频率+1
		strMap[strTmp]++;
}

typedef pair<string, int> PAIR;

bool cmp_my_value(const PAIR& lhs, const PAIR& rhs) {
	if (lhs.second != rhs.second)
	{
		return lhs.second > rhs.second;
	}
	else
	{
		return lhs.first < rhs.first;
	}
}
int count_Word(string fname)
{
	string str, strfile;
	fstream file(fname);
	while (getline(file, str))
	{
		strfile.append(str);
		strfile.append(" ");
		str.clear();
	}
	for (int i = 0; i < strfile.length(); i++)
	{
		if (!check_isVal(strfile[i]))
			strfile[i] = ' ';			 //符号位替换成为空格
	}
	transform(strfile.begin(), strfile.end(), strfile.begin(), ::tolower);
	istringstream stream(strfile);
	string word;
	while (stream >> word)
	{
		if (check(word))
		{
			count_Frequency(word);
		}
	}
	unordered_map<string, int>::const_iterator it;
	for (it = strMap.begin(); it != strMap.end(); ++it)
	{
		//cout << it->first << "：" << it->second << endl;
		word_count++;
	}
	return word_count;
}
void output_Frequency(string fname)
{
	ofstream file(fname, ios::app);
	vector<PAIR> strVec(strMap.begin(), strMap.end());
	if (strVec.size() == 0)
	{
		file.close();
		return;
	}
	sort(strVec.begin(), strVec.end(), cmp_my_value);
	for (int i = 0; i <10; ++i)
	{
		file << strVec[i].first.c_str() << ':' << strVec[i].second << endl;			//一定不能使用中文冒号！！！！！！！
	}
	file.close();
}
void file_output(string fname)
{
	ofstream file("result.txt");
	file << "characters:" << count_Ascii(fname) << endl;
	file << "words:" << count_Word(fname) << endl;
	file << "lines:" << count_Line(fname) << endl << endl;
	output_Frequency("result.txt");
	file.close();
}



int main()
{
	file_output("input.txt");
	return 0;
}



