#include "deck.h"  // Include your Deck class header

class Player {
public:
    Player();  // Constructor
    void drawInitialHand(Deck& mainDeck, int numCards, int playerNumber);// Draw initial cards from the main deck
    void playCard(Card card, int playerNumber);
    void drawCard(Deck& mainDeck);  // Draw a card from the main deck
    int getPoints() const;  // Get the player's points
    void addToPoints(int points);  // Add points to the player's total
    int getHandSize(int playerNumber) const;  // Get the size of the player's hand
    void displayHand(sf::RenderWindow& window, int playerNumber);
    //Card* Player::handleClick(const sf::Vector2f& mousePosition);

private:
    Deck hand1;
    Deck hand2;
    int points;  // Player's points
};