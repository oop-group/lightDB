#pragma once

/*
	�����ж���
	�洢�жϷ��š������жϵ�ֵ
	�ڱ�����ʱ�����жϽ��
	���硰where id=3������У�op="=",value=pData(3)
*/
class Case {
protected:
	string op;
	pData value;
public:
	virtual bool operator()(pData p)=0;
};

class Incase :public Case {
public:
	Incase(pData v) { value = v; op = "IN"; }
	bool operator()(pData p) { return false; }
};

class EqualCase :public Case {
public:
	EqualCase(pData v) { value = v; op = "="; }
	bool operator()(pData p) { return *p == *value; }
};

class NotEqualCase :public Case {
public:
	NotEqualCase(pData v) { value = v; op = "!="; }
	bool operator()(pData p) { return *p != *value; }
};

class GCase :public Case {
public:
	GCase(pData v) { value = v; op = ">"; }
	bool operator()(pData p) { return *p > *value; }
};

class LCase :public Case {
public:
	LCase(pData v) { value = v; op = "<"; }
	bool operator()(pData p) { return *p < *value; }
};

class GECase :public Case {
public:
	GECase(pData v) { value = v; op = ">="; }
	bool operator()(pData p) { return *p >= *value; }
};

class LECase :public Case {
public:
	LECase(pData v) { value = v; op = "<="; }
	bool operator()(pData p) { return *p <= *value; }
};
