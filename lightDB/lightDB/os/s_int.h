#pragma once
#include "serializable.h"

class s_int: public Serializable{
    int value;
public:
    operator int() const {return value;}
    s_int(int c): value(c){}
    string Serialize();
    static s_int* Deserialize(const string& content);
};
