#include "Card.h"
#include <iostream>

using namespace sf;

Card::Card(const std::string& color, int number) : color(color), number(number) {
    type = determineType(number);
    setCardTexture();
}

std::string Card::determineType(int number) const {
    switch (number) {
    case -1: return "Reverse";
    case -2: return "draw2";
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
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
    }
}

sf::Texture& Card::getTexture() {
    return texture;
}

sf::Texture& Card::getBackTexture() {
    static bool isBackTextureLoaded = false;
    if (!isBackTextureLoaded) {
        if (!backTexture.loadFromFile("resources/cards/EMPTYReverse.png")) {
            std::cout << "Failed to load back texture. Reason: Unable to open file" << std::endl;
        }
        isBackTextureLoaded = true;
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
        texture = other.texture;
    }
    return *this;
}

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

bool Card::isSpecial() const {
    return number < 0;
}

void Card::setColor(const std::string& newColor) {
    color = newColor;
}

