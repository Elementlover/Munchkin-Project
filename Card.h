#pragma once
#include <string>

using namespace std;

class Card
{
private:
	string name;
	string description;

public:
	Card(string cardName = "Unknown", string cardDescription = "No description")
		: name(cardName), description(cardDescription) {
	}

	// Destructor for cleanup of derived classes
	virtual ~Card() {
		// Cleanup code if needed
	}

	// Getters
	string getName() const { return name; }
	string getDescription() const { return description; }
	// Setters
	void setName(string cardName) { name = cardName; }
	void setDescription(string cardDescription) { description = cardDescription; }

	// Card Actions
	virtual void playCard() = 0;
};

