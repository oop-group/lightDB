#include<algorithm>
#include "table.h"
#include "../parser/case.h"

int Table::getColumnLength(string name) {
	return columnObjs[name]->length();
}


/*
		����µ�һ��
	*/
void Table::addColumn(string name, pColumn c) {
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
pColumn Table::getColumn(const string & name){
	return columnObjs[name];
}

/*
	��
*/
vector<Record> Table::search(vector<string> colNames,vector<vector<Condition>> condition)
{
	if (colNames[0] == "*") colNames = names;	//ѡ��ȫ����
	for (auto iter = colNames.begin(); iter != colNames.end(); iter++) {
		if (columnObjs.find(*iter) == columnObjs.end()) {
			iter = colNames.erase(iter);
		}
	}	//�������ڱ��е��ֶ���

	vector<Record> rets;
	vector<int> matchIdx=parseConditions(condition);				//�����������±�
	for (auto i : matchIdx) {
		Record ret;
		for (auto colName:colNames) {
			auto p = columnObjs[colName];
			ret.push_back(make_pair(colName,p->getData(i)));
		}
		rets.push_back(ret);
	}
	return rets;
}

/*
	ɾ
*/
void Table::del(vector<vector<Condition>> condition) {
	vector<int> matchIdx=parseConditions(condition);
	sort(matchIdx.begin(), matchIdx.end());
	int cnt,tmp;
	for (auto name : names) {
		cnt = 0;
		tmp = matchIdx[0];
		for (auto idx : matchIdx) {
			if (idx > tmp) {
				idx -= cnt;
			}
			getColumn(name)->del(idx);
			cnt++;
		}
	}
	rows = getColumnLength(names[0]);		//���¼�¼��
}

/*
	��
*/
void Table::update(map<string,pData>& datas,vector<vector<Condition>> condition) {
	vector<int> matchIdx=parseConditions(condition);
	for (auto i : matchIdx) {
		auto iter = datas.begin();
		while (iter != datas.end()) {
			string name = iter->first;
			pData data = iter->second;
			getColumn(name)->modify(i, data);
			iter++;
		}
	}
}

/*
	��
*/
void Table::insert(map<string, pData>& datas) {
	auto iter = datas.begin();
	while (iter != datas.end()) {
		string name = iter->first;
		pData data = iter->second;
		columnObjs[name]->add(data);
		iter++;
	}
	rows++;
}
/*
    Table���뷽ʽ����byte��
    [0-3]�洢�������cols
    ֮��cols��name-Column�Ķԣ���������4byte�ֱ�洢name��Column�����ݳ��ȣ���˳�δ洢��������
*/
string Table::Serialize(){
    string s;
    s_int cols(names.size());
    s+=cols.Serialize();
    for(int i=0;i<names.size();i++){
        string name(names[i]);
        s_int nameLength(name.size());
        string column=columnObjs[name]->Serialize();
        s_int colmnLength(column.size());
        s+=nameLength.Serialize();
        s+=colmnLength.Serialize();
        s+=name;
        s+=column;
    }
    return s;
}
pTable Table::Deserialize(const string& content){
    pTable table=new Table;
    int cols=*s_int::Deserialize(content.substr(0,4));
    int point=4;
    for(int i=0;i<cols;i++){
        int nameLength=*s_int::Deserialize(content.substr(point,4));
        int colmnLength=*s_int::Deserialize(content.substr(point+4,4));
        string name=content.substr(point+8,nameLength);
        pColumn column=Column::Deserialize(content.substr(point+8+nameLength,colmnLength));
        table->addColumn(name,column);
        point+=8+nameLength+colmnLength;
    }
    return table;
}

/*
	���ط����������±�����
	condition[columnName]=pCase
*/
vector<int> Table::parseConditions(vector<vector<Condition>> condition) {
	vector<int> ret;
	if (condition.size() == 0) {
		for (int i = 0; i < rows; i++) ret.push_back(i);
		return ret;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0, len1 = condition.size(); j < len1; j++) {	//��ÿ��or���
			bool match = true;		//������¼�Ƿ���������and�Ӿ�
			for (int k = 0, len2 = condition[j].size(); k < len2; k++) {	//��ÿ��and�Ӿ�
				auto pair = condition[j][k];	//pair(colname,case)
				string colName = pair.first;
				pCase c = pair.second;
				auto col = getColumn(colName);
				auto data = col->getData(i);
				bool checked = c->check(data);
				if (!checked) {	//һ��and�Ӿ䲻����
					match = false;
					break;
				}
			}
			if (match) {		//һ��or�Ӿ����
				ret.push_back(i);
				break;
			}
		}
	}
	return ret;
}