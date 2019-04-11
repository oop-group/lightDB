#include <string>
#include <iostream>
#include <vector>
#include "parser.h"
#include "mystring.h"

using namespace std;

Parser::Parser() {
	/*
		ָ��-����ӳ���
	*/
	actionMap.insert(pair<string, pActionFunc>("SELECT", this->select));
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
	Action* a=actionMap[actionType](baseStatements);				//������Ӧ�ĺ���
	return a;
}

/*
	���룺�ָ�ɴʵ������["select","*","from","stu"]������["select","a,b,c","from","stu"]
	���أ�һ��������������Ϣ��Action��ָ��
*/
Action* Parser::select(vector<string>& statement) {
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