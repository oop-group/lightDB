#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lightDB/core/column.h"

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
			Column<int> c1(ColumnType::INT, cs);
			Column<double> c2(ColumnType::DOUBLE, cs);
			Column<char> c3(ColumnType::CHAR, cs);
			c1.add(1);
			c2.add(2.333);
			c2.add(6.666);
			c3.add('a');
			Assert::AreEqual(c1.getData(0), 1);
			Assert::AreEqual(c2.getData(1), 6.666);
			Assert::AreEqual(c3.getData(0), 'a');
			c1.del(0);
			Assert::AreEqual(c1.length(), 0);
			c3.modify(0, 'b');
			Assert::AreEqual(c3.getData(0), 'b');
		}

	};
}