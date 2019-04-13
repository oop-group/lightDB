#pragma once

#include <string>

using namespace std;
class Serializable{
public:
    virtual string Serialize(){}
    static Serializable* Deserialize(const string& content);
};
