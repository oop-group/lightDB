#include "table.h"

/*
		添加新的一列
	*/
void Table::addColumn(string name, Column* c) {
	/*	
		如果原表有列且加入的列非空，判断是否等长
		如果加入的列空，填充默认数据
		如果原表没有列，修改rows
	*/
	if (cols() > 0) {
		if (c->length() > 0) {
			if (length() != c->length()) return;
		}
	}
	else rows = c->length();
	//添加新的键值对
	auto iter = columnObjs.find(name);
	if (iter == columnObjs.end()) {
		columnObjs[name] = c;
		names.push_back(name);
	}
}

/*
	返回指定字段名的对象
*/
Column & Table::getColumn(const string & name){
	return *(columnObjs[name]);
}

/*
	select [colNames] from thistable
*/
vector<vector<pair<string, string>>> Table::search(vector<string> colNames)
{
	if (colNames[0] == "*") colNames = names;	//选择全部列
	for (auto iter = colNames.begin(); iter != colNames.end(); iter++) {
		if (columnObjs.find(*iter) == columnObjs.end()) {
			iter = colNames.erase(iter);
		}
	}	//除掉不在表中的字段名

	vector<vector<pair<string, string>>> rets;

	/*
		TODO:选择条件
	*/
	for (int i = 0; i < rows; i++) {
		vector<pair<string, string>> ret;
		IntColumn* intc;
		DoubleColumn* dbc;
		CharColumn* chc;
		Column* p;
		for (auto colName : colNames) {
			p = columnObjs[colName];
			switch (p->getType())
			{
			case ColumnType::INT:
				intc = static_cast<IntColumn*>(p);
				//ret[colName] = to_string(intc->getData(i));
				ret.push_back(make_pair(colName, to_string(intc->getData(i))));
				break;
			case ColumnType::DOUBLE:
				dbc = static_cast<DoubleColumn*>(p);
				//ret[colName] = to_string(dbc->getData(i));
				ret.push_back(make_pair(colName, to_string(dbc->getData(i))));
				break;
			case ColumnType::CHAR:
				chc = static_cast<CharColumn*>(p);
				//ret[colName] = chc->getData(i);
				ret.push_back(make_pair(colName, chc->getData(i)));
				break;
			default:
				break;
			}
		}
		rets.push_back(ret);
	}
	return rets;
}
