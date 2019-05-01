#include "database.h"

#include <algorithm>

void Database::createTable(string tablename, pTable table){
    names.push_back(tablename);
    tableObjs[tablename]=table;
}

Database::~Database() {
	for (auto iter = tableObjs.begin(); iter != tableObjs.end(); iter++) {
		if (iter->second != nullptr) {
			delete iter->second;
			iter->second = nullptr;
		}
	}
	tableObjs.clear();
}

void Database::dropTable(const string& name){
    auto it=find(names.begin(),names.end(),name);
    if(it!=names.end()){
        names.erase(it);
        tableObjs.erase(name);
    }
}
pTable Database::getTable(const string& name){
    return tableObjs[name];
}
/*
    Database���뷽ʽ����byte��
    [0-3]�洢��ı���num
    ֮��num��name-Table�Ķԣ���������4byte�ֱ�洢name��Table�����ݳ��ȣ���˳�δ洢��������
*/
string Database::Serialize(){
    string s;
    s_int num(names.size());
    s+=num.Serialize();
    for(int i=0;i<names.size();i++){
        string name(names[i]);
        s_int nameLength(name.size());
        string table=tableObjs[name]->Serialize();
        s_int tableLength(table.size());
        s+=nameLength.Serialize();
        s+=tableLength.Serialize();
        s+=name;
        s+=table;
    }
    return s;
}
pDatabase Database::Deserialize(const string& content){
    pDatabase database=new Database;
    int num=*s_int::Deserialize(content.substr(0,4));
    int point=4;
    for(int i=0;i<num;i++){
        int nameLength=*s_int::Deserialize(content.substr(point,4));
        int TableLength=*s_int::Deserialize(content.substr(point+4,4));
        string name=content.substr(point+8,nameLength);
        pTable table=Table::Deserialize(content.substr(point+8+nameLength,TableLength));
        database->createTable(name,table);
        point+=8+nameLength+TableLength;
    }
    return database;
}
