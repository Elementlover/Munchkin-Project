#include "GamePlayer.h"
#include "Card.h" // Needed for shared_ptr<Card> use

GamePlayer::GamePlayer(std::string name, int level, int power, characterClass cls)
    : playerName(name), playerLevel(level), playerPower(power), activeClass(cls) {
}

int GamePlayer::getPlayerLevel() const {
    return playerLevel;
}

int GamePlayer::getPlayerPower() const {
    return playerPower;
}

characterClass GamePlayer::getActiveClass() const {
    return activeClass;
}

std::string GamePlayer::getPlayerName() const {
    return playerName;
}

void GamePlayer::setPlayerLevel(int level) {
    playerLevel = level;
}

void GamePlayer::setPlayerPower(int power) {
    playerPower = power;
}

void GamePlayer::setPlayerName(std::string name) {
    playerName = name;
}

void GamePlayer::setActiveClass(characterClass cls) {
    activeClass = cls;
}

void GamePlayer::addOneLevel() {
    playerLevel++;
}

void GamePlayer::addCardtoHand(std::shared_ptr<Card> card) {
    heldCards.push_back(card);
}

bool GamePlayer::removeCard(const std::string& cardName) {
    for (auto it = heldCards.begin(); it != heldCards.end(); ++it) {
        if ((*it)->getName() == cardName) {
            heldCards.erase(it);
            return true;
        }
    }
    return false;
}

void GamePlayer::listHeldCards() const
{
    for (const auto& heldCard : heldCards) {
        cout << "Card Name: " << heldCard->getName() << endl;
		cout << "Description: " << heldCard->getDescription() << endl;
   }
}
