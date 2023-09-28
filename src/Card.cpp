#include "Card.h"
#include <iostream>

Card::Card(const std::string& color, int number)
    : color(color), number(number), type(determineType(number)) {
    setCardTexture();
}

std::string Card::determineType(int number) const {
    switch (number) {
    case -1: return "Reverse";
    case -2: return "Draw2";
    case -3: return "Skip";
    case -4: return "Plus";
    case -5: return "Rumble";
    default: return "Common";
    }
}

void Card::setCardTexture() {
    std::string filename = "resources/cards/" + color;
    filename += (type == "Common") ? std::to_string(number) : type;
    filename += ".png";

    if (!texture.loadFromFile(filename)) {
        std::cout << "Error loading image \"" << filename << "\"" << std::endl;
    }
}

sf::Texture& Card::getTexture() {
    return texture;
}

sf::Texture& Card::getBackTexture() {
    static sf::Texture backTexture; // Make it static to load only once
    if (backTexture.getSize().x == 0) { // Check if it's not loaded yet
        backTexture.loadFromFile("resources/cards/EMPTYReverse.png");
    }
    return backTexture;
}

int Card::getNumber() const {
    return number;
}

std::string Card::getColor() const {
    return color;
}

std::string Card::getType() const {
    return type;
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        color = other.color;
        number = other.number;
        texture = other.texture; // Assuming sf::Texture supports assignment
    }
    return *this;
}

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

bool Card::isWild() {
    return number == -5 || number == -4;
}

bool Card::isSpecial() {
    return number == -1 || number == -2 || number == -3;
}

void Card::setColor(const std::string& newColor) {
    color = newColor;
}
