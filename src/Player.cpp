#include "Player.h"
#include <iostream>

// Constructor
Player::Player() : points(0) {
    // Optionally initialize the player's hand
}

// Draw initial cards from the main deck
void Player::drawInitialHand(Deck& mainDeck, int numCards) {
    for (int i = 0; i < numCards; ++i) {
        Card card = mainDeck.drawCard();
        hand.addCard(card);
    }
}

// Play a card from the player's hand
void Player::playCard(Card card) {

}

// Draw a card from the main deck
void Player::drawCard(Deck& mainDeck) {
    Card card = mainDeck.drawCard();
    hand.addCard(card);
}

// Get the player's points
int Player::getPoints() const {
    return points;
}

// Add points to the player's total
void Player::addToPoints(int pointsToAdd) {
    points += pointsToAdd;
}

// Get the size of the player's hand
int Player::getHandSize() const {
    return static_cast<int>(hand.getSize());
}



// Display the player's hand on the screen
void Player::displayHand(sf::RenderWindow& window) {

    hand.displayDeck(window);
    

}

void Player::displayHand(sf::RenderWindow& window, float Xdelta, float Ydelta) {

	hand.displayDeck(window, Xdelta, Ydelta);
}

