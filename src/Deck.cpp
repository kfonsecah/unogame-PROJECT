#include <SFML/Graphics.hpp>
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <random>

using namespace sf;



Deck::Deck() {
}

// Fill the deck with cards, including special ones
void Deck::fillDeck() {
    std::string colors[4] = { "redcard", "bluecard", "yellowcard", "greencard" };


    for (int i = 0; i < 4; i++) {
        for (int number = 0; number <= 10; ++number) {
            if (number == 0) {
                addCard(colors[i], number, 1);
            }
            else if (number == 10) {
                addSpecialCards(colors[i]);
            }
            else {
                addCard(colors[i], number, 2);
            }
        }
    }
}


void Deck::addCard(const std::string& color, int number, int count) {
    for (int i = 0; i < count; i++) {
        cards.emplace_back(color, number);
    }
}

// Helper function to add special cards for a color
void Deck::addSpecialCards(const std::string& color) {
    addCard(color, -1, 2);
    addCard(color, -2, 2);
    addCard(color, -3, 2);
    addCard("special", -4, 1);
    addCard("special", -5, 1);
}

// SHUFFLE THE DECK
void Deck::shuffle() {

    std::random_device rd;


    std::mt19937 gen(rd());


    std::shuffle(cards.begin(), cards.end(), gen);
}

// DRAW AND REMOVE THE TOP CARD FROM THE DECK
Card Deck::drawCard() {
    if (!cards.empty()) {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
    else {
        return Card("EMPTY", -1); 
    }
}


bool Deck::canReceiveCard() {

    return true;
}

void Deck::handleDeck(RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;

    float xOffset = 22.0;
    float yOffset = isControllable ? 615.0 : 7.0;

    int clickedCardIndex = detectClickedCard(window, isControllable, xOffset);

    if (clickedCardIndex != -1 && isControllable) {
        std::cout << "Clicked on card index " << clickedCardIndex << "!" << std::endl;
        sf::sleep(sf::seconds(1.0f));
        cardAction(cards[clickedCardIndex], playerHand, opponentHand, stashDeck, mainDeck, pointerToTurn);
    }
}

int Deck::detectClickedCard(RenderWindow& window, bool isControllable, float& xOffset) {
    std::vector<float> scales = computeCardScales();

    
    float yOffset = isControllable ? 615.0 : 7.0;

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite = getCardSprite(card, isControllable, scales[cardIndex]);

        cardSprite.setPosition(xOffset, yOffset);

        if (isControllable && isMouseOverCard(cardSprite, window)) {
            xOffset += isControllable ? 56.0f : 29.0f;
            window.draw(cardSprite);
            if (Mouse::isButtonPressed(Mouse::Left)) return cardIndex;
        }
        else {
            xOffset += isControllable ? 56.0f : 29.0f;
            window.draw(cardSprite);
        }
    }
    return -1;
}

std::vector<float> Deck::computeCardScales() {
    std::vector<float> scales(cards.size());
    int middleIndex = cards.size() / 2;

    for (int i = 0; i < cards.size(); i++) {
        float distanceFromCenter = abs(middleIndex - i);
        scales[i] = 0.098f;
    }
    return scales;
}

Sprite Deck::getCardSprite(Card& card, bool isControllable, float scale) {
    Sprite cardSprite;
    if (isControllable) {
        cardSprite.setTexture(card.getTexture());
    }
    else {
        cardSprite.setTexture(card.getBackTexture());
    }
    cardSprite.setScale(scale, scale);
    return cardSprite;
}

bool Deck::isMouseOverCard(Sprite& cardSprite, RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect cardBounds = cardSprite.getGlobalBounds();
    bool isMouseOver = cardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    cardSprite.setColor(isMouseOver ? sf::Color(200, 200, 200, 255) : Color(255, 255, 255, 255));
    return isMouseOver;
}


Card Deck::getTopCard() {
    if (!cards.empty()) {
        std::cout << "Top card is of stash is: " << cards.back().getColor() << " " << cards.back().getNumber() << std::endl;
        return cards.back();

    }
    else {
        // Return a special "EMPTY" card or handle this case as needed
        return Card("null", -404);
    }
}

bool Deck::isCardPlayable(Card& playedCard, Card& targetCard) {
    //std::cout << "Carta jugada: " << playedCard.getColor() << " " << playedCard.getNumber() << std::endl;
    //std::cout << "Carta en stash: " << targetCard.getColor() << " " << targetCard.getNumber() << std::endl;
    if (playedCard.isWild()) return true;
    if (playedCard.isSpecial()) return playedCard.getColor() == targetCard.getColor();
    else {
        return (playedCard.getColor() == targetCard.getColor() || playedCard.getNumber() == targetCard.getNumber());
    }
}

void Deck::removeCard(const Card& cardToRemove) {
    cards.erase(std::remove_if(cards.begin(), cards.end(),
        [&cardToRemove](const Card& card) {
            return card.getColor() == cardToRemove.getColor() &&
                card.getNumber() == cardToRemove.getNumber() &&
                card.getType() == cardToRemove.getType();
        }),
        cards.end());
}




void Deck::cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn) {
    if (isCardPlayable(card, stashDeck.getTopCard())) {
        if (card.isWild()) {
            card.setColor(getRandomColor());
            if (card.getNumber() == -5) {
                std::cout << "Wild card played!" << std::endl;
                std::cout << "Color changed to: " << card.getColor() << std::endl;
                stashDeck.addCard(card);
                playerHand.removeCard(card);
                pointerToTurn++;
            }
            else {
                std::cout << "Wild Draw Four card played!" << std::endl;
                std::cout << "Color changed to: " << card.getColor() << std::endl;
                std::cout << "Opponent draws 4 cards!" << std::endl;
                for (int i = 0; i < 4; i++) {
                    opponentHand.addCard(mainDeck.drawCard());
                }
                stashDeck.addCard(card);
                playerHand.removeCard(card);
                pointerToTurn++;
            }
        }
        else if (card.isSpecial()) {
            if (card.getNumber() == -1) {
                std::cout << "Reverse card played!" << std::endl;
                stashDeck.addCard(card);
                playerHand.removeCard(card);
                pointerToTurn++;
            }
            else if (card.getNumber() == -2) {
                std::cout << "Plus 2 card played!" << std::endl;
                std::cout << "Opponent draws 2 cards!" << std::endl;
                for (int i = 0; i < 2; i++) {
                    opponentHand.addCard(mainDeck.drawCard());
                }
                stashDeck.addCard(card);
                playerHand.removeCard(card);
                pointerToTurn++;
            }
            else if (card.getNumber() == -3) {
                std::cout << "Skip card played!" << std::endl;
                stashDeck.addCard(card);
                playerHand.removeCard(card);

                pointerToTurn += 2;
            }
        }
        else {
            std::cout << "Standard card played!" << std::endl;
            stashDeck.addCard(card);
            playerHand.removeCard(card);
            pointerToTurn++;
        }
    }
}




void Deck::displayDeck(RenderWindow& window, float xOffset, float yOffset) {
    const float windowCenterX = 1280 / 2.0f;
    const float windowCenterY = 720 / 2.0f;
    const float cardSpacing = 2.0f;

    float currentYOffset = windowCenterY - (cards.size() / 2.0f * cardSpacing);

    // Define the scale factor for the cards
    const float cardScale = 0.0999f; // Adjust this value to change the card size

    for (Card& card : cards) {
        Sprite cardSprite(card.getTexture());

        // Set the scale for the card
        cardSprite.setScale(cardScale, cardScale);

        cardSprite.setPosition(windowCenterX - cardSprite.getGlobalBounds().width / 2,
            currentYOffset - cardSprite.getGlobalBounds().height / 2);
        window.draw(cardSprite);
        currentYOffset += cardSpacing;
    }
}


// FILL THE STASH WITH ONE CARD FROM THE MAIN DECK
void Deck::initializeStash(Deck& mainDeck) {
    Card drawnCard = mainDeck.drawCard();

    // Keep drawing cards until a non-wild card is drawn
    while (drawnCard.isWild()) {
        drawnCard = mainDeck.drawCard();
    }

    std::cout << "Stash initialized with: " << drawnCard.getColor() << " " << drawnCard.getNumber() << std::endl;

    cards.push_back(drawnCard);
}


void Deck::addCard(const Card& card) {
    cards.push_back(card);  // Assuming 'cards' is a std::vector<Card> or similar collection
}

size_t Deck::getSize() const {
    return cards.size();
}

const std::vector<Card>& Deck::getCards() const {
    return cards;
}

std::string Deck::getRandomColor() {
    std::string colors[4] = { "redcard", "bluecard", "yellowcard", "greencard" };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    return colors[dist(gen)];
}