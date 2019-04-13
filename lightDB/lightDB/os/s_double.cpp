#include "s_double.h"
#include <cstring>
string s_double::Serialize(){
    char c[8];
    memcpy(c,&value,8);
    string s(8,0);
    for(int i=0;i<8;i++){
        s[i]=c[i];
    }
    return s;
}
s_double* s_double::Deserialize(const string& content){
    char c[8];
    for(int i=0;i<8;i++){
        c[i]=content[i];
    }
    double d;
    memcpy(&d,c,8);
    return new s_double(d);
}
