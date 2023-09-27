#include "Deck.h"
class Player {
public:
    Player();  // Constructor
    void drawInitialHand(Deck& mainDeck, int numCards);  // Draw initial cards from the main deck
    void playCard(Card card);
    void drawCard(Deck& mainDeck);  // Draw a card from the main deck
    int getPoints() const;  // Get the player's points
    void addToPoints(int points);  // Add points to the player's total
    int getHandSize() const;  // Get the size of the player's hand
    //void displayHand(sf::RenderWindow& window);
    //void displayHand(sf::RenderWindow& window, float xOffset, float yOffset);

    void handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);

    Deck& getHand();// Get the player's hand

    
    //Card* Player::handleClick(const sf::Vector2f& mousePosition);

private:
    Deck hand;
     // Player's hand (deck of cards)
    int points;  // Player's points
};