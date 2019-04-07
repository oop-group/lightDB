#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lightDB/core/column.h"
#include "../lightDB/core/table.h"
#include "../lightDB/core/utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestColumn)
		{
			// TODO: 在此输入测试代码
			
			
		}

		TEST_METHOD(TestTableAdd) {
			
		}

		TEST_METHOD(TestTableSearch) {
			Table t;
			Column ic(ColumnType::INT, vector<ColumnConstraint>{});
			ic.add(new Data(3));
			ic.add(new Data(4));
			t.addColumn("id", ic);
			Column cc(ColumnType::CHAR, vector<ColumnConstraint>{ColumnConstraint::PRIMARY});
			cc.add(new Data("linfang"));
			cc.add(new Data("shenxing"));
			t.addColumn("name", cc);
			Column grade(ColumnType::DOUBLE, vector<ColumnConstraint>{ColumnConstraint::UNIQUE});
			grade.add(new Data(90.0));
			grade.add(new Data(100.3));
			t.addColumn("grade", grade);
			auto res = t.search(vector<string>{"*"});
			auto res1 = t.search(vector<string>{"id", "grade"});
			map<string, Data*> datas;
			datas["id"] = new Data(123);
			datas["name"] = new Data("wangxiaofeng");
			t.update(datas);
		}

	};
}