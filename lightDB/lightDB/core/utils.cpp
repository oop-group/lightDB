#include "utils.h"

Data::Data(const char* v) {
	type = ColumnType::CHAR;
	charLen = strlen(v);
	charV = new char[1+charLen];
	for (int i = 0; i<charLen; i++) charV[i] = v[i];
	charV[charLen] = '\0';
}


Data::~Data() {
	if (type == ColumnType::CHAR && charLen > 0) {
		delete charV;
	}
}

Data::Data(const Data& d) {
	if (&d == this) return;
	type = d.getType();
	char* tmp;
	switch (type)
	{
	case ColumnType::INT:
		charLen = 0;
		intV = d.getIntV();
		break;
	case ColumnType::DOUBLE:
		charLen = 0;
		doubleV = d.getDoubleV();
		break;
	case ColumnType::CHAR:
		if (charLen > 0) delete charV;
		tmp = d.getCharV();
		charLen = strlen(tmp);
		charV = new char[charLen + 1];
		for (int i = 0; i < charLen; i++) charV[i] = tmp[i];
		charV[charLen] = '\0';
		break;
	default:
		break;
	}
}


void Data::operator=(const Data& d) {
	if (&d == this) return;
	type = d.getType();
	char* tmp;
	switch (type)	
	{
	case ColumnType::INT:
		charLen = 0;
		intV = d.getIntV();
		break;
	case ColumnType::DOUBLE:
		charLen = 0;
		doubleV = d.getDoubleV();
		break;
	case ColumnType::CHAR:
		if (charLen > 0) delete charV;
		tmp = d.getCharV();
		charLen = strlen(tmp);
		charV = new char[charLen + 1];
		for (int i = 0; i < charLen; i++) charV[i] = tmp[i];
		charV[charLen] = '\0';
		break;
	default:
		break;
	}
}

ostream& operator<<(ostream& out, const Data& d) {
	switch (d.getType())
	{
	case ColumnType::INT:
		out << d.getIntV() << endl;
		break;
	case ColumnType::DOUBLE:
		out << d.getDoubleV() << endl;
		break;
	case ColumnType::CHAR:
		out << d.getCharV() << endl;
		break;
	default:
		break;
	}
	return out;
}