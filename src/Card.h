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
    bool isSpecial() const;
    std::string Card::determineType(int number) const;
    void setColor(const std::string& color);

private:
    sf::Texture texture, backTexture;
    std::string type, color;
    int number;
};
