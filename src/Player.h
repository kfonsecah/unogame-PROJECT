#pragma once
#include <SFML/Graphics.hpp>
#include "Deck.h"

class Player {
public:
    Player();
    void drawInitialHand(Deck& mainDeck, int numCards);
    void playCard(Card card);
    void drawCard(Deck& mainDeck);
    int getPoints() const;
    void addToPoints(int points);
    int getHandSize() const;
    void handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);
    Deck& getHand();
    void addCardToHand(const Card& card);

private:
    Deck hand;
    int points;
};
