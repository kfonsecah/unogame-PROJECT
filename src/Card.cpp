#include "Card.h"

using namespace sf;

// Constructor to initialize a card with a given color and number
Card::Card(const std::string& color, int number) : color(color), number(number) {
    // Initialize other members as needed
    switch (number) {
    case -1: type = "reverse"; break;
    case -2: type = "draw2"; break;
    case -3: type = "skip"; break;
    case -4: type = "Plus"; break;
    case -5: type = "Rumble"; break;
    default: type = "Common"; break;
    }

    setTexture(); // Set the card's texture during construction
}

// Function to set the card's texture based on its color and number
void Card::setTexture() {
    // Construct the texture filename based on color and number
    std::string filename = "resources/cards/";
    filename += color;

    if (type != "Common") {
        filename += type;
    }
    else {
        filename += std::to_string(number);
    }

    filename += ".png";

    // Load and assign the texture
    if (texture.loadFromFile(filename)) {
        std::cout << "Loaded texture from: " << filename << std::endl;
    }
    else {
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
    }
}

// Function to get the card's texture
sf::Texture& Card::getTexture() {
    return texture;
}

// Function to get the card's number
int Card::getNumber() const {
    return number;
}

// Function to get the card's color
std::string Card::getColor() const {
    return color;
}

// Copy assignment operator implementation
Card& Card::operator=(const Card& other) {
    if (this != &other) {
        // Copy each member variable from 'other' to 'this'
        this->color = other.color;
        this->number = other.number;
        // Copy other members as needed
        this->texture = other.texture; // Copy texture (assuming sf::Texture supports assignment)
    }
    return *this;
}
