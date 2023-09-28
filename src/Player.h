#pragma once
#include <SFML/Graphics.hpp>
#include "Deck.h"

class Player {
public:
    Player();
    void drawInitialHand(Deck& mainDeck, int numCards);
    void playCard(Card card);
    void drawCard(Deck& mainDeck);
    int getPoints();
    void addToPoints(int points);
    int getHandSize();
    void handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);
    Deck& getHand();
    void addCardToHand(Card& card);
    Card findPlayableCard(const Card& topCard) const;

private:
    Deck hand;
    int points;
};
