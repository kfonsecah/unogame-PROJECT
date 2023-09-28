#include "Player.h"
#include <iostream>
#include <vector>

// Constructor
Player::Player() : points(0) {
    // Initialize the player's hand (optional)
}

// FUNCTION TO DRAW INITIAL CARDS FOR THE PLAYER FROM THE MAIN DECK
void Player::drawInitialHand(Deck& mainDeck, int numCards) {
    for (int i = 0; i < numCards; ++i) {
        Card card = mainDeck.drawCard();
        hand.addCard(card);
    }
}

// FUNCTION TO PLAY A CARD FROM THE PLAYER'S HAND
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

// FUNCTION TO DRAW A CARD FOR THE PLAYER FROM THE MAIN DECK
void Player::drawCard(Deck& mainDeck) {
    Card card = mainDeck.drawCard();
    hand.addCard(card);
}



// FUNCTION TO GET THE PLAYER'S CURRENT POINTS
int Player::getPoints() {
    return points;
}

// FUNCTION TO ADD POINTS TO THE PLAYER'S TOTAL
void Player::addToPoints(int pointsToAdd) {
    points += pointsToAdd;
}

// FUNCTION TO GET THE SIZE OF THE PLAYER'S HAND
int Player::getHandSize() {
    return static_cast<int>(hand.getSize());
}

// FUNCTION TO HANDLE THE PLAYER'S HAND ON THE SCREEN
void Player::handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    hand.handleDeck(window, isControllable, pointerToTurn, playerHand, opponentHand, stashDeck, mainDeck);
}

// FUNCTION TO GET THE PLAYER'S HAND
Deck& Player::getHand() {
    return hand;
}

// FUNCTION TO DRAW A CARD FROM THE MAIN DECK
void Player::addCardToHand(Card& card) {
    hand.addCard(card);
}


