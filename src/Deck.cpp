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

void Deck::handleDeck(RenderWindow& window, float xOffset, float yOffset, bool isControllable) {
    // GET THE WIDTH AND HEIGHT OF THE CARD
    const float cardWidth = cards[0].getTexture().getSize().x; // GETS THE WITH OF THE FIRST CARD IN THE DECK (ALL CARDS HAVE THE SAME WIDTH)
    const float cardHeight = cards[0].getTexture().getSize().y; // GETS THE HEIGHT OF THE FIRST CARD IN THE DECK (ALL CARDS HAVE THE SAME HEIGHT)

    // INITIALIZE THE CLICKED CARD INDEX TO -1
    int clickedCardIndex = -1;

    // LOOP THROUGH THE CARDS IN THE DECK
    // CREATES A SPRITE FOR EACH CARD AND DISPLAYS IT ON THE WINDOW
    // THE SHORT-LIVED CARD SPRITE IS DESTROYED AFTER EACH LOOP ITERATION HOWEVER AFTER BEING DRAWN ON THE WINDOW
    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite;
        float cardSpacing;;
        // SET THE CARD'S TEXTURE AND POSITION IF THE DECK IS CONTROLLABLE
        // ELSE SET THE CARD'S BACK TEXTURE, SCALE IT AND SET ITS POSITION IN ORDER TO DISPLAY IT ON THE UPPER PART OF THE WINDOW
        if (isControllable) {
            cardSpacing = 56.0f;
            cardSprite.setTexture(card.getTexture());
            cardSprite.setScale(0.0998f, 0.0998f);
        }
        else {
            cardSpacing = 29.0f;
            cardSprite.setTexture(card.getBackTexture()); // SET THE CARD'S BACK TEXTURE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            cardSprite.setScale(0.0999f, 0.0999f);
        }

        // SET THE CARD'S POSITION
        cardSprite.setPosition(xOffset, yOffset);

        // CHECK IF THE DECK IS CONTROLLABLE
        if (isControllable) {
            // CHECK IF THE MOUSE IS OVER THE CARD IF THE DECK IS CONTROLLABLE
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect cardBounds = cardSprite.getGlobalBounds();
            bool hasClicked = false;
            bool isMouseOverCard = cardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

            if (isMouseOverCard && !hasClicked) {
                // MAKES THE CARD DARKER IF THE MOUSE IS OVER IT
                cardSprite.setColor(sf::Color(200, 200, 200, 255));

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    // SETS THE CLICKED CARD INDEX IF THE MOUSE IS CLICKED OVER THE CARD
                    // clickedCardIndex RESETS TO -1 AFTER EACH LOOP ITERATION
                    clickedCardIndex = cardIndex;
                    hasClicked = true;
                    
                }
            }
            else {
                // SETS THE CARD TO ITS ORIGINAL COLOR IF THE MOUSE IS NOT OVER IT
                cardSprite.setColor(Color(255, 255, 255, 255));
            }
        }

        // DRAWS THE CARD SPRITE ON THE WINDOW AND INCREMENTS THE X OFFSET DEPENDIN ON THE CARD SPACING
        window.draw(cardSprite);
        xOffset += cardSpacing;
    }
    // CHECKS IF A CARD WAS CLICKED BY ANALYZING THE CLICKED CARD INDEX (ONLY CHANGES FROM -1 IF THE DECK IS CONTROLLABLE)
    if (clickedCardIndex != -1 && isControllable) {
        //poner metodo<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
       

        std::cout << "Clicked on card index " << clickedCardIndex << "!" << std::endl;
        //game.nextTurn();
        
       // You can also use clickedCardIndex to access the specific card in your collection
    }
}

void Deck::displayMainDeck(sf::RenderWindow& window) {
    // GET THE WIDTH AND HEIGHT OF THE CARD
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;
 
    // SET THE OFFSETS FOR THE FIRST CARD
    float yOffset = 300.0;
    float leftXOffset = 50.0;
    const float cardSpacing = 0.0f;

    // Loop through the cards and draw the main deck
    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        sf::Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(leftXOffset, yOffset);
        cardSprite.setScale(0.13f, 0.13f);

        window.draw(cardSprite);
        leftXOffset += cardSpacing;
    }

    // Display the Uno reverse card behind the main deck
    sf::Texture unoReverseTexture;
    unoReverseTexture.loadFromFile(".\\resources\\cards\\uno.png");
    sf::Sprite unoReverseSprite;
    unoReverseSprite.setTexture(unoReverseTexture);
    unoReverseSprite.setPosition(50.0, 300.0); // Adjust the position as needed
    unoReverseSprite.setScale(0.13f, 0.13f);
    window.draw(unoReverseSprite);
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