#include "Game.h"

#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"
#define BUTTON_START_GAME_PATH "./resources/start.png"



Game::Game() : _window(sf::VideoMode(1280, 720), "UNO Game") {
    // Initialize screen states
    inInitialScreen = true;
    inMainMenu = false;
    inPlayerVsPlayerScreen = false;
    inPlayerVsPCScreen = false;
    gameStarted = false;



   mainDeck.initializeDeck();
   mainDeck.shuffle();

   player1.drawInitialHand(mainDeck, 7);
   player2.drawInitialHand(mainDeck, 7);



    // Set frame rate limit
    _window.setFramerateLimit(60);

    // Load textures
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    playButtonTexture.loadFromFile(BUTTON_PLAY_PATH);
    playerVsPlayerButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PLAYER_PATH);
    playerVsPcButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PC_PATH);
    startButtonTexture.loadFromFile(BUTTON_START_GAME_PATH);

    // Configure sprites
    backgroundSprite.setTexture(backgroundTexture);

    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(580, 360);
    playButtonSprite.setScale(0.7f, 0.7f);

    playerVsPlayerButtonSprite.setTexture(playerVsPlayerButtonTexture);
    playerVsPlayerButtonSprite.setPosition(550, 220);

    playerVsPcButtonSprite.setTexture(playerVsPcButtonTexture);
    playerVsPcButtonSprite.setPosition(550, 400);

    startButtonSprite.setTexture(startButtonTexture);
    startButtonSprite.setPosition(600, 220);
    startButtonSprite.setScale(0.2f, 0.2f);
}

Game::~Game() {
}

void Game::playerVsPlayerGame() {
    // Implement player vs. player game logic
}

void Game::handleEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (inInitialScreen) {
                if (playButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inInitialScreen = false;
                    inMainMenu = true;
                }
            }
            else if (inMainMenu) {
                if (playerVsPlayerButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inMainMenu = false;
                    inPlayerVsPlayerScreen = true;
                    playerVsPlayerGame();
                    gameStarted = true;
                }
                else if (inPlayerVsPlayerScreen) {
                    // Handle in-game events for player vs. player
                }
            }
        }
    }
}

void Game::InitializeGame() {
    // Initialize the game state
}

void Game::HandlePlayerAction() {
    // Implement player action handling
}

void Game::render() {
    _window.clear();
    _window.draw(backgroundSprite);

    if (inInitialScreen) {
        _window.draw(playButtonSprite);
    }
    else if (inMainMenu) {
        _window.draw(playerVsPlayerButtonSprite);
        _window.draw(playerVsPcButtonSprite);
    }
    else if (inPlayerVsPlayerScreen) {
        // Display player's hand
        player1.displayHand(_window);
        player2.displayHand(_window, 0, 600);
        
       

    }
    else if (inPlayerVsPCScreen) {
        // Handle in-game rendering for player vs. PC
    }

    _window.display();
}

void Game::run() {
    InitializeGame();

    while (_window.isOpen()) {
        handleEvents();
        render();
        HandlePlayerAction();
    }
}

