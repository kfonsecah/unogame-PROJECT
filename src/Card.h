#pragma once

#include <SFML/Graphics.hpp> // Include the SFML library for graphics

class Card {
public:
    // Constructor to initialize a card with a given color and number
    Card(const std::string& color, int number);

    // Constructor to initialize a card with a given color and special type


    // Function to set the card's texture based on its color and number
    void setTexture();

    // Function to get the card's texture
    sf::Texture& getTexture();

    // Function to get the card's number
    int getNumber() const;

    // Function to get the card's color
    std::string getColor() const;

    // Function to get the card's type
    std::string getType() const;

    // Copy assignment operator
    Card& operator=(const Card& other);

    // Function to get the card's size
    sf::Vector2u Card::getSize() const;



    // Function to perform a card action
    void action();

    bool isSpecial() const;

private:
    sf::Texture texture; // Texture for the card
    std::string type;
    std::string color;   // Color of the card
    sf::Sprite sprite;
    int number;          // Number of the card
};