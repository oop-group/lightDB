#pragma once
#include <vector>
#include <string>

using namespace std;

/*
	����sql��һЩ���õ��ַ�������
*/

vector<string> split(string& str, string seperator);
string upper(string& str);
string strip(string&& str);
string strip(string& str);
vector<string> multipleSplit(string& str, vector<string>& seperators);
void filterSpace(vector<string>& ret);

