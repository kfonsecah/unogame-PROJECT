#pragma once
#include <SFML/Graphics.hpp>
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
    sf::Texture backgroundTexture, playButtonTexture, playerVsPlayerButtonTexture, playerVsPcButtonTexture, startButtonTexture, unoButtonTexture;
    sf::Sprite backgroundSprite, playButtonSprite, playerVsPlayerButtonSprite, playerVsPcButtonSprite, startButtonSprite, unoButtonSprite;
    bool inInitialScreen, inMainMenu, inPlayerVsPlayerScreen, inPlayerVsPCScreen, gameStarted;
    Player player1, player2;
    Deck mainDeck, deck, stashDeck;
    int currentTurn;

    void handleEvents();
    void render();
    void InitializeGame();
    void nextTurn();
    void HandleInGamePVP(sf::RenderWindow& window);
};
