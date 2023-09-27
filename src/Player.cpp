#include "Player.h"
#include <iostream>

// Constructor
Player::Player() : points(0) {
    // Initialize the player's hand (optional)
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
    // Implement your game's card-playing logic here
    // You would typically check if the card is valid to play and then remove it from the player's hand
    // For example:
    // if (isValidMove(card)) {
    //     hand.removeCard(card);
    //     // Process the card's effect and update the game state
    //     return true; // Return true if the card was successfully played
    // }
    // return false; // Return false if the card cannot be played
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
//void Player::displayHand(sf::RenderWindow& window) {
   //. hand.handleDeck(window);
//}

void Player::handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    hand.handleDeck(window, isControllable, pointerToTurn, playerHand, opponentHand, stashDeck, mainDeck);
}

Deck& Player::getHand() {
    return hand;
}


