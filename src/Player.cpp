#include "Player.h"
#include <iostream>
#include <vector>

Player::Player() : points(0) {
    // Optionally initialize the player's hand
}

void Player::drawInitialHand(Deck& mainDeck, int numCards) {
    for (int i = 0; i < numCards; ++i) {
        drawCard(mainDeck);
    }
}

void Player::drawCard(Deck& mainDeck) {
    Card card = mainDeck.drawCard();
    hand.addCard(card);
}

int Player::getPoints() {
    return points;
}

void Player::addToPoints(int value) {
    points += value;
}

int Player::getHandSize() {
    return hand.getSize();
}

void Player::handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    hand.handleDeck(window, isControllable, pointerToTurn, playerHand, opponentHand, stashDeck, mainDeck);
}

Deck& Player::getHand() {
    return hand;
}

void Player::addCardToHand(Card& card) {
    hand.addCard(card);
}




