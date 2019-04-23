#include "action.h"

void SelectAction::setColumns(vector<string>& cs) {
	if (columns.size()) columns.clear();
	for (auto i : cs) columns.push_back(i);
}

/*
void Action::addCondition(string colname, pCase c) {
	conditions.insert(pair<string, pCase>(colname, c));
}
*/



vector<string> SelectAction::getColumns() {
	return columns;
	}