#pragma once

#include <vector>
#include <map>
#include "table.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;
/*
    数据库类
*/
class Database: public Serializable{
    map<string,pTable> tableObjs; //表名-表对象
    vector<string> names;         //按照建立顺序保存表名

    public:
    //一些私有接口
    int getSize() const {return names.size();}
	vector<string> getNames() { return names; }
    void createTable(string tablename, pTable table);
    void dropTable(const string& name);
    pTable getTable(const string& name);
    string Serialize();
    static pDatabase Deserialize(const string& content);
};
