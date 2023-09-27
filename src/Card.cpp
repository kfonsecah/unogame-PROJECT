#include "Card.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

// Constructor to initialize a card with a given color and number
Card::Card(const std::string& color, int number) : color(color), number(number) {
    // Initialize other members as needed
    switch (number) {
    case -1: type = "Reverse"; break;
    case -2: type = "draw2"; break;
    case -3: type = "Skip"; break;
    case -4: type = "Plus"; break;
    case -5: type = "Rumble"; break;
    default: type = "Common"; break;
    }
    setTexture(); // Set the card's texture during construction
}

// Constructor to initialize a card with a given color and special type


// Function to set the card's texture based on its color and number
void Card::setTexture() {
    // Construct the texture filename based on color and number
    std::string filename = "resources/cards/";
    filename += color;
    //std::cout<<type<<std::endl; DEBUG
    if (type != "Common") {
        filename += type;
    }

    else {
        filename += std::to_string(number);
    }

    filename += ".png";
    //std::cout << filename << std::endl; DEBUG
    // Load and assign the texture
    if (texture.loadFromFile(filename)) {
        std::cout << "Loaded texture from directory: " << filename << std::endl;
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

std::string Card::getType() const {
    return type;
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

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

// Function to perform a card action
void Card::action() {
    // Perform the card's action
    // ...
}

// Function to check if the card is a special card
bool Card::isSpecial() const {
    return number < 0;
}