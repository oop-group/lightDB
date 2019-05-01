#pragma once

#include <string>
#include "../core/utils.h"
#include "../rename/rename.h"

/*
	条件判断类
	存储判断符号、用于判断的值
	在被调用时返回判断结果
	例如“where id=3”语句中，op="=",value=pData(3)
*/
class Case {
protected:
	string op;
	pData value;
public:
	virtual bool check(pData p)=0;
	virtual ~Case() { delete value; }
};

class Incase :public Case {
public:
	Incase(pData v) { value = v; op = "IN"; }
	bool check(pData p) { return false; }//TODO
};

class EqualCase :public Case {
public:
	EqualCase(pData v) { value = v; op = "="; }
	bool check(pData p) { return p&&value&&*p == *value; }
};

class NotEqualCase :public Case {
public:
	NotEqualCase(pData v) { value = v; op = "!="; }
	bool check(pData p) { return p && value && *p != *value; }
};

class GCase :public Case {
public:
	GCase(pData v) { value = v; op = ">"; }
	bool check(pData p) { return p && value && *p > *value; }
};

class LCase :public Case {
public:
	LCase(pData v) { value = v; op = "<"; }
	bool check(pData p) { return p && value && *p < *value; }
};

class GECase :public Case {
public:
	GECase(pData v) { value = v; op = ">="; }
	bool check(pData p) { return p && value && *p >= *value; }
};

class LECase :public Case {
public:
	LECase(pData v) { value = v; op = "<="; }
	bool check(pData p) { return p && value && *p <= *value; }
};
