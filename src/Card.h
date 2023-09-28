#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Card {
public:
    Card(const std::string& color, int number);

    // Getters
    sf::Texture& getTexture();
    sf::Texture& getBackTexture();
    int getNumber() const;
    std::string getColor() const;
    std::string getType() const;

    // Operations
    Card& operator=(const Card& other);
    sf::Vector2u getSize() const;
    void setColor(const std::string& color);

    // Type checks
    bool isSpecial();
    bool isWild();

private:
    void setCardTexture();
    std::string determineType(int number) const;

    sf::Texture texture;
    sf::Texture backTexture;
    std::string type;
    std::string color;
    int number;
};
