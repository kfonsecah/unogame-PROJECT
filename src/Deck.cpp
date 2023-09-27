#include <SFML/Graphics.hpp>
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <random>
using namespace sf;

// DEFINE THE DECK CLASS TO MANAGE A COLLECTION OF CARDS
// DECK CONSTRUCTOR

Deck::Deck() {
    // Initialize the deck as empty
    //int totalCards = 0; // INITIALIZE THE TOTAL NUMBER OF CARDS TO 0 (DEBUG)

    // No need to fill the deck here; it starts empty
    // Debug print
    // std::cout << "Total number of cards: " << totalCards << std::endl;
}

// Fill the deck with cards, including special ones
void Deck::fillDeck() {
    std::string colors[4] = { "redcard", "bluecard", "yellowcard", "greencard" };
    int totalCards = 0; // INITIALIZE THE TOTAL NUMBER OF CARDS TO 0 (DEBUG)

    for (int i = 0; i < 4; i++) {
        for (int number = 0; number <= 10; ++number) {
            if (number == 0) {
                addCard(colors[i], number, 1); // Add one zero card to the main deck per color
            }
            else if (number == 10) {
                addSpecialCards(colors[i]);
                totalCards += 8; // INCREMENT THE COUNT BY 2 FOR THE SPECIAL CARDS
            }
            else {
                addCard(colors[i], number, 2); // Add two cards of the same color and number
            }
        }
    }
    // Debug print
    // std::cout << "Total number of cards: " << totalCards << std::endl;
}

// Helper function to add cards with the same color and number
void Deck::addCard(const std::string& color, int number, int count) {
    for (int i = 0; i < count; i++) {
        cards.emplace_back(color, number);
    }
}

// Helper function to add special cards for a color
void Deck::addSpecialCards(const std::string& color) {
    addCard(color, -1, 2); // Add two Reverse cards
    addCard(color, -2, 2); // Add two Plus2 cards
    addCard(color, -3, 2); // Add two Skip cards
    addCard("special", -4, 1); // Add one Rumble card
    addCard("special", -5, 1); // Add one Rumble card
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
        // Get the top card from the deck
        Card topCard = cards.back();
        // Remove the top card from the deck
        cards.pop_back();
        // Return the drawn card
        return topCard;
    }
    else {
        // Handle the case when the deck is empty by returning a special "EMPTY" card
        return Card("EMPTY", -1); // You can create a special "EMPTY" card
    }
}

// DISPLAY THE ENTIRE DECK ON THE WINDOW AND HANDLE MOUSE INTERACTION
void Deck::displayDeck(RenderWindow& window) {
    // GET THE WIDTH AND HEIGHT OF THE CARD
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;

    // SET THE OFFSETS FOR THE FIRST CARD
    float yOffset = 7.0;
    float leftXOffset = 20.0;
    const float cardSpacing = 90.0f;

    // Initialize a variable to keep track of the clicked card index
    int clickedCardIndex = -1;

    // LOOP THROUGH THE CARDS IN THE DECK
    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        sf::Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(leftXOffset, yOffset);
        cardSprite.setScale(0.13f, 0.13f);

        // CHECK IF THE MOUSE IS OVER THE CARD
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::FloatRect cardBounds = cardSprite.getGlobalBounds();
        bool isMouseOverCard = cardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        if (isMouseOverCard) {
            // Handle the case where the mouse is over this card
            // For example, you can highlight the card or trigger an action
            // when the player clicks on it.

            // Example action: Highlight the card
            cardSprite.setColor(sf::Color(255, 255, 255, 200));

            if (Mouse::isButtonPressed(Mouse::Left)) {
                // Set the clicked card index to the current card index
                clickedCardIndex = cardIndex;
            }
        }
        else {
            // Reset the card's color if the mouse is not over it
            cardSprite.setColor(Color(255, 255, 255, 255));
        }

        window.draw(cardSprite);
        leftXOffset += cardSpacing;
    }

    // Check if a card was clicked
    if (clickedCardIndex != -1) {
        // Perform an action with the clicked card using clickedCardIndex
        std::cout << "Clicked on card " << clickedCardIndex << "!" << std::endl;
        // You can also use clickedCardIndex to access the specific card in your collection
        // cards[clickedCardIndex].performAction();
    }
}



void Deck::addCard(const Card& card) {
    cards.push_back(card);
}

size_t Deck::getSize() const {
    return cards.size();
}

const std::vector<Card>& Deck::getCards() const {
    return cards;
}