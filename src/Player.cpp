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
        hand1.addCard(card);
    }
}




void Player::playCard(Card card, int playerNumber, Deck& gameDeck) {
    // Implementa la l�gica para jugar una carta de la mano correspondiente al jugador

}

void Player::drawFromMainDeck(Deck& mainDeck) {
    // Llama a la funci�n para tomar una carta del mazo principal y agregarla a la mano del jugador
    Card card = mainDeck.drawCard();
    hand1.addCard(card);
}




// Draw a card from the main deck
void Player::drawCard(Deck& mainDeck) {
    Card card = mainDeck.drawCard();
    hand1.addCard(card);
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
int Player::getHandSize(int playerNumber) const {
    if (playerNumber == 1) {
        return static_cast<int>(hand1.getSize());
    }
    else if (playerNumber == 2) {
        return static_cast<int>(hand2.getSize());
    }
    return 0; // Maneja el caso cuando se proporciona un n�mero de jugador inv�lido
}


// Display the player's hand on the screen
void Player::displayHand(sf::RenderWindow& window, int playerNumber) {
    // Implementa la l�gica para mostrar la mano del jugador correspondiente en la ventana
    if (playerNumber == 1) {
        hand1.handleDeck(window, 100.0, 600.0, true);
    }
    else if (playerNumber == 2) {
        hand1.handleDeck(window, 100.0, 055.0, false);
    }
}

