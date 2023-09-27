#include "Player.h"
#include <iostream>

// Constructor
Player::Player() : points(0) {
    // Initialize the player's hand (optional)
}

// Draw initial cards from the main deck
void Player::drawInitialHand(Deck& mainDeck, int numCards, int playerNumber) {
    for (int i = 0; i < numCards; ++i) {
        Card card = mainDeck.drawCard();
        if (playerNumber == 1) {
            hand1.addCard(card);
        }
        else if (playerNumber == 2) {
            hand2.addCard(card);
        }
    }
}

void Player::playCard(Card card, int playerNumber) {
    // Implementa la lógica para jugar una carta de la mano correspondiente al jugador
    if (playerNumber == 1) {
        // Lógica para el jugador 1
    }
    else if (playerNumber == 2) {
        // Lógica para el jugador 2
    }
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
    return 0; // Maneja el caso cuando se proporciona un número de jugador inválido
}


// Display the player's hand on the screen
void Player::displayHand(sf::RenderWindow& window, int playerNumber) {
    // Implementa la lógica para mostrar la mano del jugador correspondiente en la ventana
    if (playerNumber == 1) {
        hand1.displayDeck(window);
    }
    else if (playerNumber == 2) {
        hand2.displayDeck(window);
    }
}


// handle click on card
//Card* Player::handleClick(const sf::Vector2f& mousePosition) {

//}
