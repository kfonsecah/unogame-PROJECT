#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Deck.h"
#include "Card.h"
#include "Player.h"

// Macros for file paths
#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BACKGROUND_IMAGE_PATH2 "./resources/background2.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"
#define BUTTON_START_GAME_PATH "./resources/start.png"
#define UNO_BUTTON_IMAGE_PATH "./resources/UnoButton.png"
#define BUTTON_SOUND_PATH "./resources/SD_NAVIGATE_59.mp3"


class Game {
public:
    Game();
    ~Game();
    void run();

private:

    sf::SoundBuffer buttonSoundBuffer;
    sf::Sound buttonSound;
    

    sf::RenderWindow _window;
    sf::Texture backgroundTexture, backgroundTexture2, playButtonTexture,
        playerVsPlayerButtonTexture, playerVsPcButtonTexture,
        startButtonTexture, unoButtonTexture;
    sf::Sprite backgroundSprite, backgroundSprite2, playButtonSprite,
        playerVsPlayerButtonSprite, playerVsPcButtonSprite,
        startButtonSprite, unoButtonSprite;

    bool inInitialScreen, inMainMenu, inPlayerVsPlayerScreen,
        inPlayerVsPCScreen, gameStarted;

    Deck mainDeck, deck, stashDeck;

    int currentTurn;
    int totalDrawnCards;

    Player player, entity;

    void handleEvents();
    void render();
    void InitializeGame();
    void HandleInGamePVP(sf::RenderWindow& window);
    void handleInGamePVE(sf::RenderWindow& window);
    void handleEatButton();
    void nextTurn();
    void initializeUnoButton();
    bool shouldDisplayUnoButton();
};