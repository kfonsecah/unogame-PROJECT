#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    void run();

    Card& operator=(const Card& other);

private:
    sf::RenderWindow _window;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture playButtonTexture;
    sf::Sprite playButtonSprite;
    sf::Texture playerVsPlayerButtonTexture;
    sf::Sprite playerVsPlayerButtonSprite;
    sf::Texture playerVsPcButtonTexture;
    sf::Sprite playerVsPcButtonSprite;
    sf::Texture startButtonTexture;
    sf::Sprite startButtonSprite;

    bool inInitialScreen;
    bool inMainMenu;
    bool inPlayerVsPlayerScreen;
    bool inPlayerVsPCScreen;
    bool gameStarted;

    Player player1;
    Player player2;

    Deck mainDeck;
    Deck gameDeck;
    Deck deck;

    int currentTurn;

    void handleEvents();
    void render();
    void playerVsPlayerGame (sf::RenderWindow& window);
    void InitializeGame();
    
    void nextTurn();
    

    void handleInGamePVE(sf::RenderWindow& window);
    void HandleInGamePVP(sf::RenderWindow& window);
    
};