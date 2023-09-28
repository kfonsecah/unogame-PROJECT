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
    int totalCards = 0;

    for (int i = 0; i < 4; i++) {
        for (int number = 0; number <= 10; ++number) {
            if (number == 0) {
                addCard(colors[i], number, 1);
            }
            else if (number == 10) {
                addSpecialCards(colors[i]);
                totalCards += 8;
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
    // USE A RANDOM DEVICE AS A SOURCE OF RANDOMNESS
    std::random_device rd;

    // USE THE RANDOM DEVICE TO SEED THE RANDOM NUMBER GENERATOR
    std::mt19937 gen(rd());

    // SHUFFLE THE CARDS USING THE RANDOM NUMBER GENERATOR
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
        return Card("EMPTY", -1); // You can create a special "EMPTY" card
    }
}




bool Deck::canReceiveCard() {
    // Implementa lógica para verificar si el mazo de juego puede recibir más cartas.
    // Por ejemplo, puedes verificar si el mazo de juego no ha alcanzado un límite máximo.
    return true; // Cambia esto según tus reglas.
}

void Deck::handleDeck(RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    // GET THE WIDTH AND HEIGHT OF THE CARD
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;

    // INITIALIZE THE CLICKED CARD INDEX TO -1
    int clickedCardIndex = -1;

    float xOffset;
    float yOffset;

    if (isControllable) {
        xOffset = 22.0;
        yOffset = 615.0;
    }
    else {
        xOffset = 22.0;
        yOffset = 7.0;
    }

    // Define the scales for the cards
    std::vector<float> scales;
    if (cards.size() == 5) {
        scales = { 0.085f, 0.09f, 0.097f, 0.09f, 0.085f };
    }
    else {
        for (int i = 0; i < cards.size(); i++) {
            scales.push_back(0.097f);
        }
    }

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite;
        float cardSpacing;

        if (isControllable) {
            cardSpacing = 56.0f;
            cardSprite.setTexture(card.getTexture());
        }
        else {
            cardSpacing = 29.0f;
            cardSprite.setTexture(card.getBackTexture());
        }

        // Adjust the card's scale based on its position
        cardSprite.setScale(scales[cardIndex], scales[cardIndex]);

        cardSprite.setPosition(xOffset, yOffset);

        if (isControllable) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect cardBounds = cardSprite.getGlobalBounds();
            bool isMouseOverCard = cardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

            if (isMouseOverCard) {
                cardSprite.setColor(sf::Color(200, 200, 200, 255));

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    clickedCardIndex = cardIndex;
                }
            }
            else {
                cardSprite.setColor(Color(255, 255, 255, 255));
            }
        }

        window.draw(cardSprite);
        xOffset += cardSpacing;
    }

    if (clickedCardIndex != -1 && isControllable) {
        std::cout << "Clicked on card index " << clickedCardIndex << "!" << std::endl;
        sf::sleep(sf::seconds(1.0f));
        cardAction(cards[clickedCardIndex], playerHand, opponentHand, stashDeck, mainDeck, pointerToTurn);
    }
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

bool Deck::isCardPlayable(const Card& playedCard, const Card& targetCard) {
    // Check if the color or number matches
    std::cout << "Played Card: " << playedCard.getColor() << " " << playedCard.getNumber() << std::endl;
    std::cout << "Target Card: " << targetCard.getColor() << " " << targetCard.getNumber() << std::endl;
    return (playedCard.getColor() == targetCard.getColor() || playedCard.getNumber() == targetCard.getNumber());
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

// EXECUTE AN ACTION BASED ON THE CARD'S PARAMETERS
#include <iostream> // Include this at the top of your file

void Deck::cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn) {
    if (isCardPlayable(card, stashDeck.getTopCard())) {
        std::cout << "Card is playable!!!!" << std::endl;
        // TO DO: SPECIAL CARDS DONT USE THE SAME NUMBER TO CHECK IF THEY ARE PLAYABLE
        // Handle regular cards
        switch (card.getNumber()) {
        case 0:
            std::swap(playerHand, opponentHand);
            break;
        case -1:
            // Reverse logic here
            break;
        case -2:
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            pointerToTurn++;
            break;
        case -3:
            pointerToTurn += 2;
            break;
        default:
            // Check for other cards with the same number in the player's hand
            for (Card& otherCard : cards) {
                if (otherCard.getNumber() == card.getNumber() && card.getNumber() > 0) {
                    stashDeck.addCard(otherCard);
                }
            }
            pointerToTurn++;
            break;
        }

        stashDeck.addCard(card);
        playerHand.removeCard(card);
    }
    else if (card.isSpecial()) {
        std::cout << "Card is WILD and playable!!!!" << std::endl;

        // Change the color of the wild card
        card.setColor(getRandomColor());

        if (card.getNumber() == -4) {
            std::cout << "Wild changed color to: " << card.getColor() << std::endl;
            stashDeck.addCard(card);
            pointerToTurn++;
        }
        else if (card.getNumber() == -5) {
            std::cout << "Wild Draw Four changed color to: " << card.getColor() << std::endl;
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            stashDeck.addCard(card);
            pointerToTurn++;
        }

        playerHand.removeCard(card);
    }
    else {
        std::cout << "Card is not playable!!!! (NOT WILD OR NOT SPECIAL) MEANS ERROR SO CHECK LAWS" << std::endl;
    }
}




void Deck::displayDeck(RenderWindow& window, float xOffset, float yOffset) {
    const float windowCenterX = 1280 / 2.0f;
    const float windowCenterY = 720 / 2.0f;
    const float cardSpacing = 2.0f; // Small spacing to see the card border

    float currentYOffset = windowCenterY - (cards.size() / 2.0f * cardSpacing);

    // Define the scale factor for the cards
    const float cardScale = 0.5f; // Adjust this value to change the card size

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
    cards.push_back(mainDeck.drawCard());
    std::cout << "Stash initialized with " << cards[0].getColor() << " " << cards[0].getNumber() << std::endl;
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