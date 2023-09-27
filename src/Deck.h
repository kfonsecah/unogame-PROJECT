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

    const std::vector<Card>& getCards() const;

    void displayDeck(sf::RenderWindow& window);
    void displayDeck(sf::RenderWindow& window, float Xdelta, float Ydelta);
    void displayMainDeck(sf::RenderWindow& window);
    void handleDeck(sf::RenderWindow& window, float xOffset, float yOffset, bool isControllable);

    void fillDeck();

    int isClicked(sf::RenderWindow& window);

private:
    void addCard(const std::string& color, int number, int count);
    void addSpecialCards(const std::string& color);
    std::vector<Card> cards;
};