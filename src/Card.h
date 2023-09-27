#pragma once

#include <SFML/Graphics.hpp>

class Card {
public:
    Card(const std::string& color, int number);

    void setCardTexture();

    sf::Texture& getTexture();

    int getNumber() const;

    std::string getColor() const;

    std::string getType() const;

    Card& operator=(const Card& other);

    sf::Vector2u getSize() const;

    sf::Texture& getBackTexture();

    void action();

    bool isSpecial() const;

private:
    sf::Texture texture;
    std::string type;
    std::string color;
    sf::Sprite sprite;
    sf::Texture backTexture;
    int number;
};