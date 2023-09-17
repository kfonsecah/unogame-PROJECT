#include "Deck.h"
#include <cstdlib>
#include <ctime>

Deck::Deck() {
    initializeDeck();
    shuffle();
}

void Deck::initializeDeck() {
    // Crea un mazo con cartas de diferentes colores y valores
    // Implementa aquí la creación de las cartas
}

void Deck::shuffle() {
    // Baraja las cartas del mazo
    std::srand(std::time(0));
    for (int i = 0; i < cards.size(); ++i) {
        int j = std::rand() % cards.size();
        std::swap(cards[i], cards[j]);
    }
}

Card Deck::dealCard() {
    // Remueve y devuelve la carta en la parte superior del mazo
    Card topCard = cards.back();
    cards.pop_back();
    return topCard;
}

int Deck::size() const {
    return cards.size();
}