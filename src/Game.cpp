#include "Game.h"

#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"

Game::Game() : _window(sf::VideoMode(626, 365), "UNO Game") {
    // Inicialmente, establece que estamos en la ventana inicial
    inInitialScreen = true;
    inMainMenu = false;
    inPlayerVsPlayerScreen = false;
    inPlayerVsPCScreen = false;

    // Carga las texturas sin control de errores
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    playButtonTexture.loadFromFile(BUTTON_PLAY_PATH);
    playerVsPlayerButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PLAYER_PATH);
    playerVsPcButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PC_PATH);

    // Configura los sprites
    backgroundSprite.setTexture(backgroundTexture);
    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(100, 200); // Ajusta la posición según tus necesidades

    playerVsPlayerButtonSprite.setTexture(playerVsPlayerButtonTexture);
    playerVsPlayerButtonSprite.setPosition(100, 200); // Ajusta la posición según tus necesidades

    playerVsPcButtonSprite.setTexture(playerVsPcButtonTexture);
    playerVsPcButtonSprite.setPosition(100, 300); // Ajusta la posición según tus necesidades
}

Game::~Game() {
}

void Game::playerVsPlayerGame() {
    // Cargar la textura del fondo en el modo Player vs Player
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        _window.clear();
        // Dibuja elementos del juego del jugador vs jugador aquí
        _window.draw(backgroundSprite); // Dibuja el fondo en este modo
        _window.display();
    }
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

                    // Cargar la textura del fondo en el modo Main Menu
                    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);

                    _window.clear();
                    _window.display();
                }
            }
            else if (inMainMenu) {
                if (playerVsPlayerButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inMainMenu = false;
                    inPlayerVsPlayerScreen = true;
                    playerVsPlayerGame();

                    _window.clear();
                    _window.display();
                }
                else if (playerVsPcButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inMainMenu = false;
                    inPlayerVsPCScreen = true;
                    // Cargar la textura del fondo en el modo Player vs PC
                    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);

                    _window.clear();
                    _window.display();
                }
            }
        }
    }
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
    else {
        // Dibuja otros elementos de juego según el estado
    }

    _window.display();
}

void Game::run() {
    while (_window.isOpen()) {
        handleEvents();

        render();
    }
}
