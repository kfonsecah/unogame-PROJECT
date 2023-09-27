#include "Deck.h"
class Player {
public:
    Player();
    void drawInitialHand(Deck& mainDeck, int numCards);
    void playCard(Card card, int playerNumber, Deck& gameDeck);
    void drawCard(Deck& mainDeck);
    int getPoints() const;
    void addToPoints(int points);
    int getHandSize(int playerNumber) const;
    void displayHand(sf::RenderWindow& window, int playerNumber);
    void removeCard(const Card& card);
    void drawFromMainDeck(Deck& mainDeck);

private:
    Deck hand1;
    Deck hand2;
    Deck otherDeck;
    int points;
};