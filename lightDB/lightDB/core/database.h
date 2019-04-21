#pragma once

#include <vector>
#include <map>
#include "table.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;
/*
    ���ݿ���
*/
class Database: public Serializable{
    map<string,pTable> tableObjs; //����-�����
    vector<string> names;         //���ս���˳�򱣴����

    public:
    //һЩ˽�нӿ�
    int getSize() const {return names.size();}
	vector<string> getNames() { return names; }
    void createTable(string tablename, pTable table);
    void dropTable(const string& name);
    pTable getTable(const string& name);
    string Serialize();
    static pDatabase Deserialize(const string& content);
};
