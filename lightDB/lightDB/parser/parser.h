#pragma once
#include <string>
#include <map>
#include "action.h"
#include "../rename/rename.h"

using namespace std;

/*
	SQL��������
*/
class Parser {
private:
	static Action* select(vector<string>& statement);
	map<string, pActionFunc> actionMap;
public:
	Parser();
	Action* parse(string& input);
	
};
