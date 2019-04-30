#include "s_char.h"
#include <cstring>

string s_char::Serialize(){
    return string(value);
}
s_char* s_char::Deserialize(const string& content){
    char* c=new char[content.size()];
    strcpy_s(c,content.size(),content.c_str());
    return new s_char(c);
}
