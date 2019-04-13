#include <string>
#include <iostream>
#include <vector>
#include "../rename/rename.h"
#include "parser.h"
#include "mystring.h"
#include "../core/utils.h"

using namespace std;

Parser::Parser() {
	/*
		指令-函数映射表
	*/
	actionMap.insert(pair<string, pActionFunc>("SELECT", this->select));
	actionMap.insert(pair<string, pActionFunc>("UPDATE", this->update));
	actionMap.insert(pair<string, pActionFunc>("DELETE", this->del));
	actionMap.insert(pair<string, pActionFunc>("INSERT", this->insert));
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
	Action* a=actionMap[actionType](baseStatements,inputs[0]);				//运行相应的函数
	return a;
}

/*
	输入：分割成词的命令，如["select","*","from","stu"]，或者["select","a,b,c","from","stu"]
	返回：一个包含了上述信息的Action类指针
*/
Action* Parser::select(vector<string>& statement,string& str) {
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

/*
	输入：["update",["tablename"],"set","attrname","=","value"]
	返回：包含上述信息的指针
*/
Action* Parser::update(vector<string>& statement,string& str) {
	UpdateAction* action = new UpdateAction();
	action->setType("update");
	action->setTable(statement[1]);
	/*
		先假设输入只有一个col=val
	*/
	vector<string> equation = split(statement[3],"=");
	string colName = equation[0];
	string value = equation[1];
	if (value.find('\'')!=string::npos || value.find('"')!=string::npos) {
		value = value.substr(1, value.size() - 2);
		value = strip(value);
		action->setData(colName, new Data(value.c_str()));
	}
	else {
		//先假设这是浮点数
		double fvalue = atof(strip(value).c_str());
		action->setData(colName, new Data(fvalue));
	}
	return action;
}

/*
	INSERT INTO oop_info(stu_id, stu_name) VALUES (2018011343, "a") 
*/
Action* Parser::insert(vector<string>& statement,string& str) {
	InsertAction* action = new InsertAction();
	action->setType("insert");
	vector<string> tmp = split(str, "values");
	if (tmp.size() != 2) {
		tmp = split(str, "VALUES");
	}
	string insertInto = tmp[0];	//insert into oopinfo(stu_id,stu_name)
	int leftParenthesis = insertInto.find("(");
	int rightParenthesis = insertInto.find(")");
	string colnamesStr = insertInto.substr(leftParenthesis + 1, rightParenthesis - leftParenthesis - 1);
	vector<string> colnames = split(colnamesStr, ",");	//["stu_id"," stu_name"]
	filterSpace(colnames);								//["stu_id","stu_name"]
	string tmp1 = tmp[1];							//" (2018011343,"a")"
	leftParenthesis = tmp1.find("(");
	rightParenthesis = tmp1.find(")");
	string valuesStr = tmp1.substr(leftParenthesis + 1, rightParenthesis - leftParenthesis - 1);
	vector<string> values = split(valuesStr, ",");
	filterSpace(values);							//["2018011343","a"]
	for (int i = 0, len = colnames.size(); i < len; i++) {
		string value = values[i];
		if (value.find('\'') != string::npos || value.find('"') != string::npos) {
			action->setData(colnames[i], new Data(value.c_str()));
		}
		else {
			double fvalue = atof(value.c_str());
			action->setData(colnames[i], new Data(fvalue));
		}
	}
	return action;
}

/*
	delete from tablename
*/
Action* Parser::del(vector<string>& statement,string& str) {
	DeleteAction* action = new DeleteAction();
	action->setTable(statement[2]);
	action->setType("delete");
	return action;
}