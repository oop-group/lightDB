#include <iostream>
#include "engine.h"
#include "../parser/parser.h"

using namespace std;

/*
	�����û����룬ִ��sql��䣬��ӡ���
*/
void Engine::run() {
	string input;
	string ret;
	while (1) {
		getline(cin, input);
		ret = execute(input);
		if (ret.size() > 0) cout << ret << endl;
	}
}

/*
	�����ַ�����������ΪSql�����������ַ������
	�����select���󣬷���������
	�������󣬷��ؿ��ַ���
*/
string Engine::execute(string& str) {
	Action* action = Parser().parse(str);
	/*
		����action-function mapִ��ָ���Ķ���
	*/
	return "";
}