#pragma once
#include <vector>
#include <string>

using namespace std;

/*
	解析sql中一些常用的字符串操作
*/

vector<string> split(string& str, string seperator);
string upper(string& str);
string strip(string&& str);
string strip(string& str);
vector<string> multipleSplit(string& str, vector<string>& seperators);
void filterSpace(vector<string>& ret);

