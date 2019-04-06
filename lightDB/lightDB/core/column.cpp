#include "column.h"

Column::Column(const ColumnType& t, const vector<ColumnConstraint>& cs)
{
	for (int j = 0, len = cs.size(); j < len; j++) constraints.push_back(cs[j]);
	type = t;
	rows = 0;
}




