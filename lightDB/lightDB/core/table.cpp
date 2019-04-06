#include "table.h"

/*
		����µ�һ��
	*/
void Table::addColumn(string name, Column* c) {
	/*	
		���ԭ�������Ҽ�����зǿգ��ж��Ƿ�ȳ�
		���������пգ����Ĭ������
		���ԭ��û���У��޸�rows
	*/
	if (cols() > 0) {
		if (c->length() > 0) {
			if (length() != c->length()) return;
		}
	}
	else rows = c->length();
	//����µļ�ֵ��
	auto iter = columnObjs.find(name);
	if (iter == columnObjs.end()) {
		columnObjs[name] = c;
		names.push_back(name);
	}
}

/*
	����ָ���ֶ����Ķ���
*/
Column & Table::getColumn(const string & name){
	return *(columnObjs[name]);
}

/*
	select [colNames] from thistable
*/
vector<vector<pair<string, string>>> Table::search(vector<string> colNames)
{
	if (colNames[0] == "*") colNames = names;	//ѡ��ȫ����
	for (auto iter = colNames.begin(); iter != colNames.end(); iter++) {
		if (columnObjs.find(*iter) == columnObjs.end()) {
			iter = colNames.erase(iter);
		}
	}	//�������ڱ��е��ֶ���

	vector<vector<pair<string, string>>> rets;

	/*
		TODO:ѡ������
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
