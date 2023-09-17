#pragma once

#include <SFML/Graphics.hpp>

class Card {
public:
    Card(const std::string& imagePath, const sf::IntRect& textureRect);
    void display(sf::RenderWindow& window);

    // Other necessary methods and attributes

private:
    sf::Texture texture;
    sf::Sprite sprite;
    
};
 