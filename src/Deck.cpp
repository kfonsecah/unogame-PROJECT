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
    const float cardWidth = cards[0].getTexture().getSize().x; // GETS THE WITH OF THE FIRST CARD IN THE DECK (ALL CARDS HAVE THE SAME WIDTH)
    const float cardHeight = cards[0].getTexture().getSize().y; // GETS THE HEIGHT OF THE FIRST CARD IN THE DECK (ALL CARDS HAVE THE SAME HEIGHT)

    // INITIALIZE THE CLICKED CARD INDEX TO -1
    int clickedCardIndex = -1;

    // LOOP THROUGH THE CARDS IN THE DECK
    // CREATES A SPRITE FOR EACH CARD AND DISPLAYS IT ON THE WINDOW
    // THE SHORT-LIVED CARD SPRITE IS DESTROYED AFTER EACH LOOP ITERATION HOWEVER AFTER BEING DRAWN ON THE WINDOW
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

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite;
        float cardSpacing;



        // SET THE CARD'S TEXTURE AND POSITION IF THE DECK IS CONTROLLABLE
        // ELSE SET THE CARD'S BACK TEXTURE, SCALE IT AND SET ITS POSITION IN ORDER TO DISPLAY IT ON THE UPPER PART OF THE WINDOW
        if (isControllable) {
            cardSpacing = 56.0f;
            cardSprite.setTexture(card.getTexture());
            cardSprite.setScale(0.097f, 0.097f);
        }
        else {
            cardSpacing = 29.0f;
            cardSprite.setTexture(card.getBackTexture()); // SET THE CARD'S BACK TEXTURE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            cardSprite.setScale(0.097f, 0.097f);
        }

        // SET THE CARD'S POSITION
        cardSprite.setPosition(xOffset, yOffset);

        // CHECK IF THE DECK IS CONTROLLABLE
        if (isControllable) {
            // CHECK IF THE MOUSE IS OVER THE CARD IF THE DECK IS CONTROLLABLE
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect cardBounds = cardSprite.getGlobalBounds();
            bool isMouseOverCard = cardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

            if (isMouseOverCard) {
                // MAKES THE CARD DARKER IF THE MOUSE IS OVER IT
                cardSprite.setColor(sf::Color(200, 200, 200, 255));

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    // SETS THE CLICKED CARD INDEX IF THE MOUSE IS CLICKED OVER THE CARD
                    // clickedCardIndex RESETS TO -1 AFTER EACH LOOP ITERATION
                    clickedCardIndex = cardIndex;

                }
            }
            else {
                // SETS THE CARD TO ITS ORIGINAL COLOR IF THE MOUSE IS NOT OVER IT
                cardSprite.setColor(Color(255, 255, 255, 255));
            }
        }

        // DRAWS THE CARD'S SPRITE ON THE WINDOW AND INCREMENTS THE X OFFSET DEPENDIN ON THE CARD SPACING
        window.draw(cardSprite);
        xOffset += cardSpacing;
    }
    // CHECKS IF A CARD WAS CLICKED BY ANALYZING THE CLICKED CARD INDEX (ONLY CHANGES FROM -1 IF THE DECK IS CONTROLLABLE)
    if (clickedCardIndex != -1 && isControllable) {
        std::cout << "Clicked on card index " << clickedCardIndex << "!" << std::endl;
        // MAKE THE GAME WAIT FOR 1 SECOND

        sf::sleep(sf::seconds(1.0f));
        // PERFORM AN ACTION BASED ON THE CARD'S NUMBER, COLOR, AND CHARACTERISTICS

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
void Deck::cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn) {
    if (isCardPlayable(card, stashDeck.getTopCard())) {
        std::cout << "Card is playable!!!!" << std::endl;

        // Add the card to the stash
        stashDeck.addCard(card);

        // Remove the card from the player's hand
        playerHand.removeCard(card);

        // Implement Uno rules
        switch (card.getNumber()) {
        case -1: // Reverse
            // Assuming you have a way to reverse turn order, implement it here
            break;
        case -2: // Plus2
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            break;
        case -3: // Skip
            // Skip opponent's turn. If you're increasing pointerToTurn at the end, 
            // you might want to increase it by 2 here to skip the opponent's turn.
            pointerToTurn += 2;
            return;
        case -4: // Wild Plus4
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            // You might want to add color selection logic for Wild cards
            break;
        case -5: // Rumble (I assume this is Wild)
            // You might want to add color selection logic for Wild cards
            break;
        default:
            break;
        }

        // Increase the turn pointer
        pointerToTurn++;
    }
}


void Deck::displayDeck(RenderWindow& window, float xOffset, float yOffset) {
    // SET THE SPACING BETWEEN CARDS
    const float cardSpacing = 57.0f;

    // LOOP THROUGH THE CARDS IN THE DECK
    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(xOffset, yOffset);

        window.draw(cardSprite);
        xOffset += cardSpacing;
    }
}
// FILL THE STASH WITH ONE CARD FROM THE MAIN DECK
void Deck::initializeStash(Deck& mainDeck) {
    cards.push_back(mainDeck.drawCard());
    std::cout << "Stash initialized with " << cards[0].getColor() << " " << cards[0].getNumber() << std::endl;
}

void Deck::drawStash(sf::RenderWindow& window, float xOffset, float yOffset) {
    // Check if there are cards in the stash
    if (!cards.empty()) {
        const float cardSpacing = 0.0f;
        int lastCardIndex = cards.size() - 1; // Index of the last card in the stash

        // Get the last card in the stash
        Card& lastCard = cards[lastCardIndex];

        // Create a sprite for the last card and set its texture and position
        Sprite lastCardSprite;
        lastCardSprite.setTexture(lastCard.getTexture());
        lastCardSprite.setPosition(xOffset, yOffset);

        // Draw the last card sprite
        window.draw(lastCardSprite);
    }
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