#include "s_int.h"
#include <cstring>
string s_int::Serialize(){
    char c[4];
    memcpy(c,&value,4);
    string s(4,0);
    for(int i=0;i<4;i++){
        s[i]=c[i];
    }
    return s;
}
s_int* s_int::Deserialize(const string& content){
    char c[4];
    for(int i=0;i<4;i++){
        c[i]=content[i];
    }
    int d;
    memcpy(&d,c,4);
    return new s_int(d);
}
