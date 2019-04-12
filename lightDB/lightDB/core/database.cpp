#include "database.h"

#include <algorithm>

void Database::createTable(string tablename, pTable table){
    names.push_back(tablename);
    tableObjs[tablename]=table;
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
    Database编码方式（按byte）
    [0-3]存储库的表数num
    之后num个name-Table的对，先用两个4byte分别存储name和Table的数据长度，再顺次存储二者数据
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
