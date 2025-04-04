#pragma once
#include <string>

using namespace std;

class characterClass
{
private:
	string name;

public:
	characterClass(string className = "Unknown") : name(className) {}

    // Getter
    string getName() const { return name; }

    // Setter
    void setName(string className) { name = className; }
};

