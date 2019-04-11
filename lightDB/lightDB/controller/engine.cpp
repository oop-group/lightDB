#include <iostream>
#include "engine.h"
#include "../parser/parser.h"

using namespace std;

/*
	接受用户输入，执行sql语句，打印结果
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
	接受字符串，将其作为Sql解析，返回字符串结果
	如果是select请求，返回请求结果
	其他请求，返回空字符串
*/
string Engine::execute(string& str) {
	Action* action = Parser().parse(str);
	/*
		根据action-function map执行指定的动作
	*/
	return "";
}