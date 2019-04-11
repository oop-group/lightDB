#include <iostream>
#include <string>
#include "core/column.h"
#include "core/table.h"
#include "controller/engine.h"
using namespace std;

int main() {
	/*Table t;
	Column ic(ColumnType::INT, vector<ColumnConstraint>{});
	ic.add(new Data(3));
	ic.add(new Data(4));
	t.addColumn("id", &ic);
	Column cc(ColumnType::CHAR, vector<ColumnConstraint>{ColumnConstraint::PRIMARY});
	cc.add(new Data("linfang"));
	cc.add(new Data("shenxing"));
	t.addColumn("name", &cc);
	Column grade(ColumnType::DOUBLE, vector<ColumnConstraint>{ColumnConstraint::UNIQUE});
	grade.add(new Data(90.0));
	grade.add(new Data(100.3));
	t.addColumn("grade", &grade);
	auto res = t.search(vector<string>{"*"});
	auto res1 = t.search(vector<string>{"id", "grade"});
	map<string, pData> datas;
	datas["id"] = new Data(123);
	datas["name"] = new Data("wangxiaofeng");
	t.update(datas);
	map<string, pData> data1;
	data1["id"] = new Data(456);
	data1["name"] = new Data("chenjunhai");
	t.insert(data1);*/
	Engine().run();
	system("pause");
	return 0;
}