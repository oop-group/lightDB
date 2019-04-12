#pragma once
#include "serializable.h"

class s_double: public Serializable{
    double value;
public:
    operator double() const {return value;}
    s_double(double c): value(c){}
    string Serialize();
    static s_double* Deserialize(const string& content);
};
