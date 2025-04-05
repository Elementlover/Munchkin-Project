#pragma once
#include <string>

using namespace std;

class characterClass
{
private:
	string name;

public:
	characterClass(string className = "Unknown") : name(className) {}

    // Getters
    string getName() const { return name; }

    // Setters
    void setName(string className) { name = className; }
};

