#pragma once

#include "Deck.h"
#include "Card.h"
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void drawInitialHand(Deck& mainDeck, int numCards);
    void playCard(Card card);
    void drawCard(Deck& mainDeck);
    int getPoints() const;
    void addToPoints(int points);
    int getHandSize() const;
    void displayHand(sf::RenderWindow& window);
    void displayHand(sf::RenderWindow& window, float Xdelta, float Ydelta);

private:
    Deck hand;
    Deck hand2;
    int points;
};
