#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "../rename/rename.h"
#include "parser.h"
#include "mystring.h"
#include "../core/utils.h"
#include "../controller/engine.h"

using namespace std;

Parser::Parser(Engine* e) {
	engine = e;	
	/*
		指令-函数映射表
	*/
	actionMap.insert(pair<string, pActionFunc>("SELECT", this->select));
	actionMap.insert(pair<string, pActionFunc>("UPDATE", this->update));
	actionMap.insert(pair<string, pActionFunc>("DELETE", this->del));
	actionMap.insert(pair<string, pActionFunc>("INSERT", this->insert));
	/*
		操作符-判断类一览表
	*/
	caseMap.insert(pair<string, pCaseFunc>("=", this->equal));
	caseMap.insert(pair<string, pCaseFunc>("!=", this->notEqual));
	caseMap.insert(pair<string, pCaseFunc>(">", this->greater));
	caseMap.insert(pair<string, pCaseFunc>("<", this->less));
	caseMap.insert(pair<string, pCaseFunc>("<=", this->lesseq));
	caseMap.insert(pair<string, pCaseFunc>(">=", this->greatereq));
}



pAction Parser::parse(string& input) {
	vector<string> inputs = split(input, "where");
	if (inputs.size() != 2) inputs = split(input, "WHERE");
	string actionType;
	istringstream is0(inputs[0]);
	is0 >> actionType;
	actionType = upper(actionType);
	pAction action = actionMap[actionType](inputs[0],engine);
	/*
		解析条件子句，将其信息加入到action对象中
	*/
	if (inputs.size() == 1) {	//无条件
		return action;
	}
	istringstream is1(inputs[1]);
	vector<string> seperators{ "and", "or", "AND", "OR" };
	vector<string> exprs = multipleSplit(inputs[1], seperators);
	int len = exprs.size();
	for (int i = 0; i < len; i++) {
		string expr = exprs[i];
		int pos;
		string col, op, value;
		auto it = caseMap.begin();
		while (it != caseMap.end()) {
			pos = expr.find(it->first);	//操作符在pos中的位置
			if (pos != string::npos) {	//找到正确操作符
				col =expr.substr(0, pos);
				col = strip(col);
				op = it->first;
				value = expr.substr(pos + op.size(), expr.size() - pos - op.size());
				value = strip(value);
				/*if (value.find('\'') != string::npos || value.find('"') != string::npos) {		//字符串
					action->addCondition(col, caseMap[op](new Data(value.c_str())));
				}
				else {
					action->addCondition(col, caseMap[op](new Data(atof(value.c_str()))));		//数值型
				}*/
				auto colObj = engine->getCurrentDb()->getTable(action->getTable())->getColumn(col);
				switch (colObj->getType())
				{
				case ColumnType::CHAR:
					value = value.substr(1, value.size() - 2);	//去掉引号
					value = strip(value);
					action->addCondition(col, caseMap[op](new Data(value.c_str())));
					break;
				case ColumnType::DOUBLE:
					action->addCondition(col, caseMap[op](new Data(atof(value.c_str()))));
					break;
				case ColumnType::INT:
					action->addCondition(col, caseMap[op](new Data(atoi(value.c_str()))));
					break;
				default:
					break;
				}
			}
			it++;
		}
	}
	return action;
}

pAction Parser::select(string& str,pEngine engine) {
	SelectAction* action = new SelectAction();
	action->setType("search");		//命令名称	
	istringstream is(str);
	string cmd;
	is >> cmd;	//select
	string tmp;
	vector<string> cs;	//列名
	bool isAll = false;	//是否选择全部列
	while (is >> tmp) {
		if (tmp == "from") break;
		if (tmp == "*") {
			is >> tmp;	//from
			isAll = true;
			break;
		}
		vector<string> colnames = split(tmp, ",");
		filterSpace(colnames);
		for (int i = 0, len = colnames.size(); i < len; i++) cs.push_back(colnames[i]);
	}
	
	string tableStr;
	is >> tableStr;
	action->setTable(tableStr);
	if (isAll) {
		auto table = engine->getCurrentDb()->getTable(tableStr);
		cs = table->getColNames();
	}
	action->setColumns(cs);
	return action;
}

pAction Parser::update(string& str,pEngine engine) {
	UpdateAction* action = new UpdateAction();
	action->setType("update");
	string cmd, table,set;
	istringstream is(str);
	is >> cmd>> table >> set;
	action->setTable(table);
	string expr,col,value;
	is >> expr;
	int eqpos = expr.find("=");
	if (eqpos != string::npos) {
		col = expr.substr(0, eqpos);
		if (eqpos == expr.size() - 1) {	//"attrname="
			is >> value;
		}
		else {							//"attrname=value"
			value = expr.substr(eqpos + 1, expr.size() - 1 - eqpos);
		}
	}
	else {
		col = expr;
		string s2;
		is >> s2;
		if (s2.size() == 1) {	//"="
			is >> value;
		}
		else {					//"=value"
			value = s2.substr(1, s2.size() - 1);
		}
	}
	auto colType = engine->getCurrentDb()->getTable(table)->getColumn(col)->getType();
	value = strip(value);
	switch (colType)
	{
	case ColumnType::CHAR:
		value = value.substr(1, value.size() - 2);	//去掉引号
		value = strip(value);
		action->setData(col, new Data(value.c_str()));
		break;
	case ColumnType::DOUBLE:
		action->setData(col, new Data(atof(value.c_str())));
		break;
	case ColumnType::INT:
		action->setData(col, new Data(atoi(value.c_str())));
		break;
	default:
		break;
	}
	/*if (value.find('\'')!=string::npos || value.find('"')!=string::npos) {
		value = value.substr(1, value.size() - 2);
		value = strip(value);
		action->setData(col, new Data(value.c_str()));
	}
	else {
		//先假设这是浮点数
		double fvalue = atof(strip(value).c_str());
		action->setData(col, new Data(fvalue));
	}*/
	return action;
}

/*
	INSERT INTO oop_info(stu_id, stu_name) VALUES (2018011343, "a") 
*/
pAction Parser::insert(string& str,pEngine engine) {
	InsertAction* action = new InsertAction();
	action->setType("insert");
	vector<string> tmp = split(str, "values");
	if (tmp.size() != 2) {
		tmp = split(str, "VALUES");
	}
	istringstream is(tmp[0]);
	int startInto = tmp[0].find("into");
	if (startInto == string::npos) startInto = tmp[0].find("INTO");
	string expr = tmp[0].substr(startInto + 5, tmp[0].size() - 5 - startInto);
	expr = strip(expr);
	int leftParenthesis = expr.find("(");
	string table = expr.substr(0, leftParenthesis);
	table = strip(table);
	action->setTable(table);
	int rightParenthesis = expr.find(")");
	string colnamesStr = expr.substr(leftParenthesis + 1, rightParenthesis - leftParenthesis - 1);
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
		string col = colnames[i];
		ColumnType colType = engine->getCurrentDb()->getTable(table)->getColumn(col)->getType();
		value = strip(value);
		switch (colType)
		{
		case ColumnType::CHAR:
			value = value.substr(1, value.size() - 2);	//去掉引号
			value = strip(value);
			action->setData(col, new Data(value.c_str()));
			break;
		case ColumnType::DOUBLE:
			action->setData(col, new Data(atof(value.c_str())));
			break;
		case ColumnType::INT:
			action->setData(col, new Data(atoi(value.c_str())));
			break;
		default:
			break;
		}
		/*if (value.find('\'') != string::npos || value.find('"') != string::npos) {
			action->setData(colnames[i], new Data(value.c_str()));
		}
		else {
			double fvalue = atof(value.c_str());
			action->setData(colnames[i], new Data(fvalue));
		}*/
	}
	return action;
}

/*
	delete from tablename
*/
pAction Parser::del(string& str,pEngine engine) {
	DeleteAction* action = new DeleteAction();
	action->setType("delete");
	string from, table,del;
	istringstream is(str);
	is >> del>>from >> table;
	action->setTable(table);
	return action;
}

/*
	构造case对象并返回指针
*/
pCase Parser::equal(pData value) {
	return new EqualCase(value);
}

pCase Parser::notEqual(pData value) {
	return new NotEqualCase(value);
}

pCase Parser::less(pData value) {
	return new LCase(value);
}

pCase Parser::lesseq(pData value) {
	return new LECase(value);
}

pCase Parser::greater(pData value) {
	return new GCase(value);
}

pCase Parser::greatereq(pData value) {
	return new GECase(value);
}



