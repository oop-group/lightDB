#include <string>
#include <iostream>
#include <vector>
#include "parser.h"
#include "mystring.h"

using namespace std;

Parser::Parser() {
	/*
		指令-函数映射表
	*/
	actionMap.insert(pair<string, pActionFunc>("SELECT", this->select));
}



Action* Parser::parse(string& input) {
	//将命令和条件分开
	vector<string> inputs = split(input, string("where"));
	if (inputs.size() == 0) inputs = split(input, string("WHERE"));

	//将操作按照空格分成单词select,*,from,xxx等
	vector<string> baseStatements=split(inputs[0],string(" "));
	filterSpace(baseStatements);		//去掉空白字符
	if (baseStatements.size() < 2) return NULL;			//输入错误
	string actionType=upper(baseStatements[0]);			//指令：select,update等
	if (actionMap.find(actionType) == actionMap.end()) return NULL;	//非法命令
	Action* a=actionMap[actionType](baseStatements);				//运行相应的函数
	return a;
}

/*
	输入：分割成词的命令，如["select","*","from","stu"]，或者["select","a,b,c","from","stu"]
	返回：一个包含了上述信息的Action类指针
*/
Action* Parser::select(vector<string>& statement) {
	SelectAction* action = new SelectAction();
	action->setType("search");		//命令名称	
	action->setTable(statement[statement.size() - 1]);	//待查询表名
	string s = statement[1];
	if (s == "*") {
		vector<string> cs{s};
		action->setColumns(cs);
	}
	else {
		vector<string> cs = split(s, ",");
		action->setColumns(cs);
	}
	return action;
}