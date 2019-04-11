#include "action.h"

void SelectAction::setColumns(vector<string>& cs) {
	if (columns.size()) columns.clear();
	for (auto i : cs) columns.push_back(i);
}