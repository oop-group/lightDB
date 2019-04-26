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
	actionMap["SELECT"] = select;
	actionMap["UPDATE"] = update;
	actionMap["DELETE"] = del;
	actionMap["INSERT"] = insert;
	actionMap["CREATETABLE"] = createTb;

	actionMap["USE"] = use;
	actionMap["SHOWDATABASES"] = show;
	actionMap["SHOWCOLUMNS"] = showCol;
	actionMap["DROP"] = dropDb;
	actionMap["CREATEDATABASE"] = createDb;
	/*
		操作符-判断类一览表
	*/
	caseMap["="] = equal;
	caseMap["!="] = notEqual;
	caseMap[">"] = greater;
	caseMap["<"] = less;
	caseMap["<="] = lesseq;
	caseMap[">="] = greatereq;
}



pAction Parser::parse(string& input) {
	//去掉末尾分号
	input = input.substr(0, input.size() - 1);
	vector<string> inputs = split(input, "where");
	if (inputs.size() != 2) inputs = split(input, "WHERE");
	string actionType;
	istringstream is0(inputs[0]);
	is0 >> actionType;
	actionType = upper(actionType);
	if (actionType == "CREATE") {
		string tableOrDb;
		is0 >> tableOrDb;
		actionType += upper(tableOrDb);
	}
	else if (actionType == "SHOW") {
		string tableOrDb;
		is0 >> tableOrDb;
		actionType += upper(tableOrDb);
	}
	pAction action = actionMap[actionType](inputs[0],engine);
	/*
		解析条件子句，将其信息加入到action对象中
	*/
	if (inputs.size() == 1) {	//无条件
		return action;
	}
	istringstream is1(inputs[1]);
	vector<string> orseps{ "or","OR" };
	vector<string> andseps{ "and","AND" };
	vector<string> orexprs = multipleSplit(inputs[1], orseps);	//先按照or分割
	int len = orexprs.size();
	vector<vector<Condition>> conditions;
	for (int i = 0; i < len; i++) {
		string tmpexpr = orexprs[i];
		vector<string> andexprs = multipleSplit(tmpexpr, andseps);	//再按照and分割
		int len1 = andexprs.size();
		vector<Condition> tmpconditions;
		for (int j = 0; j < len1; j++) {
			string expr = andexprs[j];	//独立的and子句
			int pos;
			string col, op, value;
			auto it = caseMap.begin();
			while (it != caseMap.end()) {
				pos = expr.find(it->first);	//操作符在pos中的位置
				if (pos != string::npos) {	//找到正确操作符
					col = expr.substr(0, pos);
					col = strip(col);
					op = it->first;
					value = expr.substr(pos + op.size(), expr.size() - pos - op.size());
					value = strip(value);
					auto colObj = engine->getCurrentDb()->getTable(static_cast<TableOpAction*>(action)->getTable())->getColumn(col);
					switch (colObj->getType())
					{
					case ColumnType::CHAR:
						value = value.substr(1, value.size() - 2);	//去掉引号
						value = strip(value);
						tmpconditions.push_back(make_pair(col, caseMap[op](new Data(value.c_str()))));
						break;
					case ColumnType::DOUBLE:
						tmpconditions.push_back(make_pair(col, caseMap[op](new Data(atof(value.c_str())))));
						break;
					case ColumnType::INT:
						tmpconditions.push_back(make_pair(col, caseMap[op](new Data(atoi(value.c_str())))));
						break;
					default:
						break;
					}
				}
				it++;
			}
		}
		conditions.push_back(tmpconditions);
	}
	static_cast<TableOpAction*>(action)->setCondition(conditions);
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

pAction Parser::showCol(string& str, pEngine engine) {
	ShowColAction* action = new ShowColAction();
	action->setType("showcol");
	string cmd,from,table;
	istringstream is(str);
	is >> cmd >> cmd >> from>>table;		//show columns from
	action->setTable(table);
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

pAction Parser::createTb(string& str, pEngine engine) {
	CreateTbAction* action = new CreateTbAction();
	action->setType("createtb");
	string cmd;
	int tmp = str.find("table");
	if (tmp == string::npos) tmp = str.find("TABLE");
	str = str.substr(tmp + 6, str.size() - tmp-6);
	str = strip(str);
	tmp = str.find("(");
	string table = str.substr(0, tmp);
	table = strip(table);
	action->setTable(table);	//数据表名
	string expr = str.substr(tmp + 1, str.size() - tmp - 3);
	vector<string> cols = split(expr,",");	
	string colname, type, constraint,constraintpart,col;
	int len = cols.size();
	for (int i = 0; i < len - 1; i++) {	//前n-1个子句:stu_id int not null
		col = cols[i];
		istringstream is(col);
		is >> colname>>type;
		constraint = "";
		while (is >> constraintpart) constraint += constraintpart;
		action->addItem(colname, str2type(type), str2constraints(constraint));
	}
	col=cols[len - 1];	//最后一个子句：primary key(stu_id)
	int leftParentthis = col.find("(");
	int rightParentthis = col.find(")");
	colname = col.substr(leftParentthis + 1, rightParentthis - 1 - leftParentthis);
	action->setPrimaryKey(colname);
	return action;
}

/*
	切换活动数据库
*/
pAction Parser::use(string& str, pEngine engine) {
	UseAction* action = new UseAction();
	istringstream is(str);
	string cmd, db;
	is >> cmd>>db;
	action->setType("use");
	action->setDbName(db);
	return action;
}

pAction Parser::show(string& str, pEngine engine) {
	ShowAction* action = new ShowAction();
	action->setType("show");
	return action;
}

pAction Parser::dropDb(string& str, pEngine engine) {
	DropDbAction* action = new DropDbAction();
	action->setType("dropdb");
	istringstream is(str);
	string cmd, db;
	is >> cmd >> cmd>>db;
	action->setDbName(db);
	return action;
}

pAction Parser::createDb(string& str, pEngine engine) {
	CreateDbAction* action = new CreateDbAction();
	action->setType("createdb");
	istringstream is(str);
	string cmd, db;
	is >> cmd >> cmd >> db;
	action->setDbName(db);
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



