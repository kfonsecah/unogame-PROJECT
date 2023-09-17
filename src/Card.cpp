#include "Card.h"

Card::Card(const std::string& imagePath, const sf::IntRect& textureRect) {
    if (!texture.loadFromFile(imagePath, textureRect)) {
        // Error handling if texture loading fails
    }

    sprite.setTexture(texture);
}

void Card::display(sf::RenderWindow& window) {
    window.draw(sprite);
}

