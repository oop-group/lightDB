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
/*
    Data编码方式（按byte）
    [0]:bit7-bit2为终止符;bit1和bit0合起来存储类型,00 01 10分别代表int double char*
    若类型为int，则[1-4]存储value
    若类型为double，则[1-8]存储value
    若类型为char*，则之后全部为数据
*/
string Data::Serialize(){
    string s;
    //Serializable ss[3]={s_int(intV),s_double(doubleV),s_char(charV)};
    //int i=static_cast<int>(type);
    //s+=(char)i;
    //s+=ss[i].Serialize();
    char c=static_cast<int>(type);
    s+=c;
    switch(type){
    case ColumnType::INT:
        {
            s_int si(intV);
            s+=si.Serialize();
        }
        break;
    case ColumnType::DOUBLE:
        {
            s_double sd(doubleV);
            s+=sd.Serialize();
        }
        break;
    case ColumnType::CHAR:
        {
            s_char sc(charV);
            s+=sc.Serialize();
        }
        break;
    }
    return s;
}
pData Data::Deserialize(const string& content){
    switch(content[0]){
    case 0:
        return new Data(*s_int::Deserialize(content.substr(1,content.size()-1)));
    case 1:
        return new Data(*s_double::Deserialize(content.substr(1,content.size()-1)));
    case 2:
        return new Data(*s_char::Deserialize(content.substr(1,content.size()-1)));
    default:
        //error
        return nullptr;
    }
}
