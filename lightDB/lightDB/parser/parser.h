#pragma once
#include <string>
#include <map>
#include "action.h"
#include "case.h"
#include "../rename/rename.h"

using namespace std;

/*
	SQLÓï¾ä½âÎöÆ÷
*/
class Parser {
private:
	static pAction select(string& str);
	static pAction update(string& str);
	static pAction del(string& str);
	static pAction insert(string& str);
	map<string, pActionFunc> actionMap;	
	static pCase equal(pData value);
	static pCase notEqual(pData value);
	static pCase less(pData value);
	static pCase greater(pData value);
	static pCase lesseq(pData value);
	static pCase greatereq(pData value);
	map<string, pCaseFunc> caseMap;

public:
	Parser();
	Action* parse(string& input);
	
};
