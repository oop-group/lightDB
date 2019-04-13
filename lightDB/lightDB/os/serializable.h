#pragma once

#include <string>

using namespace std;
class Serializable{
public:
	virtual string Serialize() { return ""; }
    static Serializable* Deserialize(const string& content);
};
