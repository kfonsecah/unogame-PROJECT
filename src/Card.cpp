#include "Card.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

Card::Card(const std::string& color, int number) : color(color), number(number) {
    switch (number) {
    case -1: type = "Reverse"; break;
    case -2: type = "draw2"; break;
    case -3: type = "Skip"; break;
    case -4: type = "Plus"; break;
    case -5: type = "Rumble"; break;
    default: type = "Common"; break;
    }
    setCardTexture();
}

void Card::setCardTexture() {
    std::string filename = "resources/cards/";
    filename += color;
    if (type != "Common") {
        filename += type;
    }
    else {
        filename += std::to_string(number);
    }
    filename += ".png";

    if (texture.loadFromFile(filename)) {
        std::cout << "Loaded texture from directory: " << filename << std::endl;
    }
    else {
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
    }
}

sf::Texture& Card::getTexture() {
    return texture;
}

sf::Texture& Card::getBackTexture() {
    backTexture.loadFromFile("resources/cards/Uno.png");
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
        this->color = other.color;
        this->number = other.number;
        this->texture = other.texture;
    }
    return *this;
}

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

void Card::action() {
    // Perform the card's action
}

bool Card::isSpecial() const {
    return number < 0;
}