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
		ָ��-����ӳ���
	*/
	actionMap.insert(pair<string, pActionFunc>("SELECT", this->select));
	actionMap.insert(pair<string, pActionFunc>("UPDATE", this->update));
	actionMap.insert(pair<string, pActionFunc>("DELETE", this->del));
	actionMap.insert(pair<string, pActionFunc>("INSERT", this->insert));
}



Action* Parser::parse(string& input) {
	//������������ֿ�
	vector<string> inputs = split(input, string("where"));
	if (inputs.size() == 0) inputs = split(input, string("WHERE"));

	//���������տո�ֳɵ���select,*,from,xxx��
	vector<string> baseStatements=split(inputs[0],string(" "));
	filterSpace(baseStatements);		//ȥ���հ��ַ�
	if (baseStatements.size() < 2) return NULL;			//�������
	string actionType=upper(baseStatements[0]);			//ָ�select,update��
	if (actionMap.find(actionType) == actionMap.end()) return NULL;	//�Ƿ�����
	Action* a=actionMap[actionType](baseStatements,inputs[0]);				//������Ӧ�ĺ���
	return a;
}

/*
	���룺�ָ�ɴʵ������["select","*","from","stu"]������["select","a,b,c","from","stu"]
	���أ�һ��������������Ϣ��Action��ָ��
*/
Action* Parser::select(vector<string>& statement,string& str) {
	SelectAction* action = new SelectAction();
	action->setType("search");		//��������	
	action->setTable(statement[statement.size() - 1]);	//����ѯ����
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
	���룺["update",["tablename"],"set","attrname","=","value"]
	���أ�����������Ϣ��ָ��
*/
Action* Parser::update(vector<string>& statement,string& str) {
	UpdateAction* action = new UpdateAction();
	action->setType("update");
	action->setTable(statement[1]);
	/*
		�ȼ�������ֻ��һ��col=val
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
		//�ȼ������Ǹ�����
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