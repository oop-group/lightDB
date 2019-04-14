#pragma once
#include <string>
#include <map>
#include "action.h"
#include "case.h"
#include "../rename/rename.h"

using namespace std;

class Engine;

/*
	SQL��������
*/
class Parser {
private:
	static pAction select(string& str,pEngine engine);
	static pAction update(string& str,pEngine engine);
	static pAction del(string& str,pEngine engine);
	static pAction insert(string& str,pEngine engine);
	map<string, pActionFunc> actionMap;	
	static pCase equal(pData value);
	static pCase notEqual(pData value);
	static pCase less(pData value);
	static pCase greater(pData value);
	static pCase lesseq(pData value);
	static pCase greatereq(pData value);
	map<string, pCaseFunc> caseMap;
	Engine* engine;

public:
	Parser(Engine* e);
	Action* parse(string& input);
	
};
