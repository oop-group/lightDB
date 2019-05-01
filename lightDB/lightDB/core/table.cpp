#include<algorithm>
#include "table.h"
#include "../parser/case.hpp"

int Table::getColumnLength(string name) {
	return columnObjs[name]->length();
}

Table::~Table()
{
	for (auto iter = columnObjs.begin(); iter != columnObjs.end(); iter++) {
		if (iter->second != nullptr) {
			delete iter->second;
			iter->second = nullptr;
		}
	}
	columnObjs.clear();
}
/*
		添加新的一列
	*/
void Table::addColumn(string name, pColumn c) {
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
pColumn Table::getColumn(const string & name){
	return columnObjs[name];
}

/*
	查
*/
vector<Record> Table::search(vector<string> colNames,vector<vector<Condition>>&& condition)
{
	if (colNames[0] == "*") colNames = names;	//选择全部列
	for (auto iter = colNames.begin(); iter != colNames.end(); iter++) {
		if (columnObjs.find(*iter) == columnObjs.end()) {
			iter = colNames.erase(iter);
		}
	}	//除掉不在表中的字段名

	vector<Record> rets;
	vector<int> matchIdx=parseConditions(std::move(condition));				//符合条件的下标
	for (auto i : matchIdx) {
		Record ret;
		ret.setKey(keyCol);
		for (auto colName:colNames) {
			auto p = columnObjs[colName];
			ret[colName] = p->getData(i);
		}
		rets.push_back(ret);
	}
	return rets;
}

/*
	删
*/
void Table::del(vector<vector<Condition>>&& condition) {
	vector<int> matchIdx=parseConditions(std::move(condition));
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
	rows = getColumnLength(names[0]);		//更新记录数
}

/*
	改
*/
void Table::update(map<string,pData>& datas,vector<vector<Condition>>&& condition) {
	vector<int> matchIdx=parseConditions(std::move(condition));
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
	插入新的一行
*/
void Table::insert(map<string, pData>& datas) {
	for (auto name : names) {
		auto col = columnObjs[name];
		if (datas.find(name)!=datas.end()) {
			col->add(datas[name]);
		}
		else {
			col->add(col->getDefaultValue());
		}
	}
	rows++;
}
/*
    Table编码方式（按byte）
    [0-3]存储表的列数cols
    之后cols个name-Column的对，先用两个4byte分别存储name和Column的数据长度，再顺次存储二者数据
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
	返回符合条件的下标数组
	condition[columnName]=pCase
*/
vector<int> Table::parseConditions(vector<vector<Condition>>&& condition) {
	vector<int> ret;
	if (condition.size() == 0) {
		for (int i = 0; i < rows; i++) ret.push_back(i);
		return ret;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0, len1 = condition.size(); j < len1; j++) {	//对每个or语句
			bool match = true;		//该条记录是否满足所有and子句
			for (int k = 0, len2 = condition[j].size(); k < len2; k++) {	//对每个and子句
				string colName=condition[j][k].first;	//pair(colname,case)
				pCase c = condition[j][k].second;
				pColumn col = getColumn(colName);
				pData data = col->getData(i);
				bool checked = c->check(data);
				if (!checked) {	//一个and子句不成立
					match = false;
					break;
				}
			}
			if (match) {		//一个or子句成立
				ret.push_back(i);
				break;
			}
		}
	}
	return ret;
}