#include "Game.h"

#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"
#define BUTTON_START_GAME_PATH "./resources/start.png"

Game::Game() : _window(sf::VideoMode(626, 365), "UNO Game") {
    // Inicialmente, establece que estamos en la ventana inicial
    inInitialScreen = true;
    inMainMenu = false;
    inPlayerVsPlayerScreen = false;
    inPlayerVsPCScreen = false;


    // Carga las texturas
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    playButtonTexture.loadFromFile(BUTTON_PLAY_PATH);
    playerVsPlayerButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PLAYER_PATH);
    playerVsPcButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PC_PATH);
    startButtonTexture.loadFromFile(BUTTON_START_GAME_PATH);


    // Configura los sprites
    backgroundSprite.setTexture(backgroundTexture);

    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(235, 140);
    playButtonSprite.setScale(0.6f, 0.6f);// Adjust the scale factor 

    playerVsPlayerButtonSprite.setTexture(playerVsPlayerButtonTexture);
    playerVsPlayerButtonSprite.setPosition(210, 220);
      
    playerVsPcButtonSprite.setTexture(playerVsPcButtonTexture);
    playerVsPcButtonSprite.setPosition(210, 140);
    startButtonSprite.setTexture(startButtonTexture);

    startButtonSprite.setPosition(260, 140);
    startButtonSprite.setScale(0.2f, 0.2f); // Adjust the scale factor 
     

}

Game::~Game() {
}

void Game::playerVsPlayerGame() {

    std::cout<<"playerVsPlayerGame"<<std::endl;

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
                }
                else if (playerVsPcButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inMainMenu = false;
                    inPlayerVsPCScreen = true;
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
    else if (inPlayerVsPlayerScreen) {
        _window.draw(startButtonSprite);
        
    }
    else if (inPlayerVsPCScreen) {
		_window.draw(startButtonSprite);
    }

    _window.display();
}

void Game::run() {
    while (_window.isOpen()) {
        handleEvents();
        render();
    }
}
