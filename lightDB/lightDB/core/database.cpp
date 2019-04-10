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
