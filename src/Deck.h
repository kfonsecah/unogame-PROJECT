#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle();
    Card drawCard();
    void addCard(const Card& card);
    size_t getSize() const;
    void cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn);
    void initializeStash(Deck& mainDeck);
    bool isCardPlayable(const Card& playedCard, const Card& targetCard);
    Card getTopCard();
    const std::vector<Card>& getCards() const;
    bool canReceiveCard();
    void handleDeck(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);
    void displayDeck(sf::RenderWindow& window, float xOffset, float yOffset);
    void fillDeck();
    void drawStash(sf::RenderWindow& window, float xOffset, float yOffset);
    void removeCard(const Card& card);
    std::string getRandomColor();

private:
    sf::Clock clickCooldown;
    void addCard(const std::string& color, int number, int count);
    void addSpecialCards(const std::string& color);
    std::vector<Card> cards;
};
