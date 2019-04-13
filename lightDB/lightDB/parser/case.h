#pragma once

/*
	�����ж���
	�洢�жϷ��š������жϵ�ֵ
	���硰where id=3������У�=���жϷ��ţ�3�������жϵ�ֵ
*/
class Case {
protected:
	string op;
	pData value;
};

class Incase :public Case {
public:
	Incase(pData v) { value = v; op = "IN"; }
};

class EqualCase :public Case {
public:
	EqualCase(pData v) { value = v; op = "="; }
};

class NotEqualCase :public Case {
public:
	NotEqualCase(pData v) { value = v; op = "!="; }
};

class GCase :public Case {
public:
	GCase(pData v) { value = v; op = ">"; }
};

class LCase :public Case {
public:
	LCase(pData v) { value = v; op = "<"; }
};

class GECase :public Case {
public:
	GECase(pData v) { value = v; op = ">="; }
};

class LECase :public Case {
public:
	LECase(pData v) { value = v; op = "<="; }
};
