#include "mystring.h"


/*
	���ַ�������ĳЩ�ַ����ֳ�����
*/
vector<string> split(string& str, string seperator) {
	vector<string> ret;
	int len = str.size();
	int slen = seperator.size();
	int last = -1;	//��һ��matchƬ�ε����һ���ַ���str�е��±�
	for (int i = 0; i < len; i++) {
		if (str[i] == seperator[0]) {
			bool match = true;
			for (int j = 1; j < slen; j++) {
				if (seperator[j] != str[i + j]) {
					match = false;
					break;
				}
			}
			if (match == true) {
				ret.push_back(str.substr(last + 1, i - 1 - last));
				last = i +slen- 1;
				i += slen - 1;
			}
		}
	}
	ret.push_back(str.substr(last + 1, len - 1 - last));
	return ret;
}

/*
	����ָ��ַ�
*/
vector<string> multipleSplit(string& str, vector<string>& seperators) {
	vector<string> ret;
	int len = str.size();
	int ssize = seperators.size();
	int last = -1;	//��һ��matchƬ�ε����һ���ַ���str�е��±�
	for (int i = 0; i < len; i++) {
		for (int k = 0; k < ssize; k++) {		//���͵�k���ָ����Ƿ�ƥ��
			bool anyMatch = false;				//��һ���ָ���ƥ�伴��Ϊtrue
			string seperator = seperators[k];
			int slen = seperator.size();
			if (str[i] == seperator[0]) {
				bool match = true;
				for (int j = 1; j < slen; j++) {
					if (seperator[j] != str[i + j]) {
						match = false;
						break;
					}
				}
				if (match == true) {
					ret.push_back(str.substr(last + 1, i - 1 - last));
					last = i + slen - 1;
					i += slen - 1;
					anyMatch = true;
					break;
				}
			}
		}
	}
	ret.push_back(str.substr(last + 1, len - 1 - last));
	return ret;
}


/*	
	���ַ�����Ϊ��д
*/
string upper(string& s) {
	for (int i = 0, len = s.size(); i < len; i++) {
		if (s[i]>='a'&&s[i]<='z') s[i] = (char)(s[i] - 'a' + 'A');
	}
	return s;
}	

/*
	�Ƿ�Ϊ�հ��ַ�
*/
bool isBlank(string& str) {
	int cnt = str.size();
	for (int i = 0, len = str.size(); i < len; i++) {
		char c = str[i];
		if (c == ' ' || c == '\t' || c == '\n') cnt--;
	}
	return cnt == 0;
}

string strip(string& str) {
	int i = 0, len = str.size();
	while (i < len) {
		char c = str[i];
		if (c == ' ' || c == '\t' || c == '\n') i++;
		else break;
	}
	int r = len - 1;
	while (r >= 0) {
		char c = str[r];
		if (c == ' ' || c == '\t' || c == '\n') r--;
		else break;
	}
	return str.substr(i, r - i + 1);
}
/*
	ȥ���հ��ַ�
*/
void filterSpace(vector<string>& strs) {
	auto it = strs.begin();
	while (it != strs.end()) {
		*it=strip(*it);
		if (it->size() == 0) it = strs.erase(it);
		else it++;	
	}
}