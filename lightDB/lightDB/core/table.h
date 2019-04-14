#pragma once

#include <map>
#include "column.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;

/*
	���ݱ���
	������Ϊkey���ж���Ϊvalue�������ֵ��ʽ�洢����������
*/
class Table: public Serializable{
	map<string, pColumn> columnObjs;	//����-�ж���
	int rows;							//����
	vector<string> names;				//���ղ���˳�򱣴�������

	int getColumnLength(string name);	//ָ�������еļ�¼��
	vector<int> parseConditions(map<string,pCase>& condition);	
public:
	Table() :rows(0) {}

	void addColumn(string name,  pColumn c);
	pColumn getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }
	vector<string> getColNames() { return names; }

	/*
		��ɾ���
	*/
	vector<Record> search(vector<string> colNames,map<string,pCase>& condition);
	void del(map<string,pCase>& condition);
	void update(map<string,pData>& datas,map<string,pCase>& condition);
	void insert(map<string, pData>& datas);
	string Serialize();
	static pTable Deserialize(const string& content);
};
