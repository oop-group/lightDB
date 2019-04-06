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
			vector<ColumnConstraint> cs;
			cs.push_back(ColumnConstraint::PRIMARY);
			cs.push_back(ColumnConstraint::UNIQUE);
			IntColumn a(ColumnType::INT, cs);
			DoubleColumn b(ColumnType::DOUBLE, cs);
			a.add(3);
			a.add(4);
			a.add(5);
			a.add(8);
			a.del(2);
			a.del(0);
			a.modify(2, 1);
			Assert::AreEqual(a.length(), 2);
			
		}

		TEST_METHOD(TestTable) {
			Table t;
			IntColumn* ic = new IntColumn(ColumnType::INT, vector<ColumnConstraint>{});
			ic->add(3);
			ic->add(4);
			t.addColumn("id", ic);
			CharColumn* cc = new CharColumn(ColumnType::CHAR, vector<ColumnConstraint>{ColumnConstraint::PRIMARY});
			t.addColumn("name", cc);
		}

	};
}