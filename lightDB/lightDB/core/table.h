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
	vector<int> parseConditions(vector<vector<Condition>>&& condition);	
public:
	Table() :rows(0) {}
	~Table();
	void addColumn(string name,  pColumn c);
	pColumn getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }
	vector<string> getColNames() { return names; }

	/*
		��ɾ���
	*/
	vector<Record> search(vector<string> colNames,vector<vector<Condition>>&&);
	void del(vector<vector<Condition>>&&);
	void update(map<string,pData>& datas,vector<vector<Condition>>&&);
	void insert(map<string, pData>& datas);
	string Serialize();
	static pTable Deserialize(const string& content);
};
