#pragma once
#include "serializable.h"

class s_char: public Serializable{
    char* value;
public:
    operator char*() const {return value;}
    s_char(char* c): value(c){}
    string Serialize();
    static s_char* Deserialize(const string& content);
};
