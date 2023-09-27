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

    int currentTurn;

    void handleEvents();
    void render();
    void playerVsPlayerGame();
    void InitializeGame();
    void handleEventsPlayerVsPlayer(sf::Event event);
    void nextTurn();
};