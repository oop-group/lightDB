#include "mystring.h"


/*
	将字符串按照某些字符串分成两半
*/
vector<string> split(string& str, string seperator) {
	vector<string> ret;
	int len = str.size();
	int slen = seperator.size();
	int last = -1;	//上一个match片段的最后一个字符在str中的下标
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
	多个分割字符
*/
vector<string> multipleSplit(string& str, vector<string>& seperators) {
	vector<string> ret;
	int len = str.size();
	int ssize = seperators.size();
	int last = -1;	//上一个match片段的最后一个字符在str中的下标
	for (int i = 0; i < len; i++) {
		for (int k = 0; k < ssize; k++) {		//检查和第k个分隔符是否匹配
			bool anyMatch = false;				//有一个分隔符匹配即置为true
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
	将字符串改为大写
*/
string upper(string& s) {
	for (int i = 0, len = s.size(); i < len; i++) {
		if (s[i]>='a'&&s[i]<='z') s[i] = (char)(s[i] - 'a' + 'A');
	}
	return s;
}	

/*
	是否为空白字符
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
	去掉空白字符
*/
void filterSpace(vector<string>& strs) {
	auto it = strs.begin();
	while (it != strs.end()) {
		*it=strip(*it);
		if (it->size() == 0) it = strs.erase(it);
		else it++;	
	}
}