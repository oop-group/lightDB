#include<algorithm>
#include "table.h"

int Table::getColumnLength(string name) {
	return columnObjs[name].length();
}


/*
		����µ�һ��
	*/
void Table::addColumn(string name, Column& c) {
	/*	
		���ԭ�������Ҽ�����зǿգ��ж��Ƿ�ȳ�
		���������пգ����Ĭ������
		���ԭ��û���У��޸�rows
	*/
	if (cols() > 0) {
		if (c.length() > 0) {
			if (length() != c.length()) return;
		}
	}
	else rows = c.length();
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
	return columnObjs[name];
}

/*
	��
*/
vector<vector<pair<string, Data*>>> Table::search(vector<string> colNames)
{
	if (colNames[0] == "*") colNames = names;	//ѡ��ȫ����
	for (auto iter = colNames.begin(); iter != colNames.end(); iter++) {
		if (columnObjs.find(*iter) == columnObjs.end()) {
			iter = colNames.erase(iter);
		}
	}	//�������ڱ��е��ֶ���

	vector<vector<pair<string, Data*>>> rets;	
	vector<int> matchIdx;				//�����������±�
	/*
		TODO:ѡ������
	*/
	for (int i = 0; i < rows; i++) matchIdx.push_back(i);
	for (auto i : matchIdx) {
		vector<pair<string, Data*>> ret;
		for (auto colName:colNames) {
			auto p = columnObjs[colName];
			ret.push_back(make_pair(colName,p.getData(i)));
		}
		rets.push_back(ret);
	}
	return rets;
}

/*
	ɾ
*/
void Table::del() {
	/*
		TODO:��������ѡ����Ӧ����
	*/
	vector<int> matchIdx;
	for (int i = 0; i < rows; i++) matchIdx.push_back(i);
	sort(matchIdx.begin(), matchIdx.end());
	int cnt,tmp;
	for (auto name : names) {
		cnt = 0;
		tmp = matchIdx[0];
		for (auto idx : matchIdx) {
			if (idx > tmp) {
				idx -= cnt;
			}
			getColumn(name).del(idx);
			cnt++;
		}
	}
	rows = getColumnLength(names[0]);		//���¼�¼��
}

/*
	��
*/
void Table::update(map<string,Data*>& datas) {
	vector<int> matchIdx;
	/*
		TODO:��������ѡ��matchIdx
	*/
	for (int i = 0; i < rows; i++) matchIdx.push_back(i);
	for (auto i : matchIdx) {
		auto iter = datas.begin();
		while (iter != datas.end()) {
			string name = iter->first;
			Data* data = iter->second;
			getColumn(name).modify(i, data);
			iter++;
		}
	}
}

/*
	��
*/
void Table::insert(map<string, Data*>& datas) {
	auto iter = datas.begin();
	while (iter != datas.end()) {
		string name = iter->first;
		Data* data = iter->second;
		columnObjs[name].add(data);
		iter++;
	}
	rows++;
}
