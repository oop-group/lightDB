#pragma once
#include <string>
#include <map>
#include "action.h"
#include "../rename/rename.h"

using namespace std;

/*
	SQLÓï¾ä½âÎöÆ÷
*/
class Parser {
private:
	static Action* select(vector<string>& statement,string& str);
	static Action* update(vector<string>& statement,string& str);
	static Action* del(vector<string>& statement,string& str);
	static Action* insert(vector<string>& statement,string& str);
	map<string, pActionFunc> actionMap;
public:
	Parser();
	Action* parse(string& input);
	
};
